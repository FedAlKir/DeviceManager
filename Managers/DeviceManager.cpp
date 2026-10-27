#include "DeviceManager.h"

#include "Device.h"
#include "EDeviceType.h"
#include "TemperatureSensor.h"
#include "GPSReceiver.h"
#include "NetworkMonitor.h"

#include "../external/rapidjson/document.h"
#include "../external/rapidjson/writer.h"
#include "../external/rapidjson/istreamwrapper.h"
#include "../external/rapidjson/ostreamwrapper.h"

#include<iostream>
#include<memory>
#include<fstream>

bool DeviceManager::idIsValid(const int id) const {
    return devices.find(id) != devices.end();
}

DeviceManager::DeviceManager() : nextDeviceId(1) {}

int DeviceManager::addDevice(const EDeviceType deviceType, const std::string& name) {
    switch (deviceType) {
        case EDeviceType::TEMPERATURE_SENSOR: {
            TemperatureSensor d(nextDeviceId, deviceType, name);
            devices[nextDeviceId++] = std::make_unique<TemperatureSensor>(d);
            logger.logDeviceAddition(d.getId(), &d);
            break;
        }
        case EDeviceType::GPS_RECEIVER: {
            GPSReceiver d(nextDeviceId, deviceType, name);
            devices[nextDeviceId++] = std::make_unique<GPSReceiver>(d);
            logger.logDeviceAddition(d.getId(), &d);
            break;
        }
        case EDeviceType::NETWORK_MONITOR: {
            NetworkMonitor d(nextDeviceId, deviceType, name);
            devices[nextDeviceId++] = std::make_unique<NetworkMonitor>(d);
            logger.logDeviceAddition(d.getId(), &d);
            break;
        }
        default: {
            std::cerr << "UNKNOWN_DEVICE_TYPE_ERROR" << std::endl;
            logger.logDeviceAddition(nextDeviceId, nullptr);
        }
    }

    return nextDeviceId - 1;
}

bool DeviceManager::removeDevice(const int id) {
    if (!idIsValid(id)) {
        logger.logDeviceRemoving(id, nullptr);
        return false;
    }

    logger.logDeviceRemoving(id, &*devices[id]);
    devices.erase(id);

    return true;
}

void DeviceManager::printAllDevices() const {
    for (const auto& [id, device] : devices) {
        std::cout << device->getInfo() << std::endl;
    }
}

void DeviceManager::tickAllDevices() {
    for (const auto& [id, device] : devices) {
        device->tick();
    }
    logger.logDevicesUpdate();
}

bool DeviceManager::turnDeviceOn(const int id) {
    if (!idIsValid(id)) {
        logger.logDeviceActivation(id, nullptr);
        return false;
    }

    devices[id]->turnOn();
    logger.logDeviceActivation(id, &*devices[id]);
    std::cout << devices[id]->getName() << " is now ON" << std::endl;
    return true;
}

bool DeviceManager::turnDeviceOff(const int id) {
    if (!idIsValid(id)) {
        logger.logDeviceDeactivation(id, nullptr);
        return false;
    }

    devices[id]->turnOff();
    logger.logDeviceDeactivation(id, &*devices[id]);
    std::cout << devices[id]->getName() << " is now OFF" << std::endl;
    return true;
}

Device* DeviceManager::findDeviceById(const int id) const {
    if (!idIsValid(id)) {
        return nullptr;
    }

    return devices.find(id)->second.get();
}

bool DeviceManager::save() {

    rapidjson::Document document(rapidjson::kObjectType);
    auto& alloc = document.GetAllocator();

    document.AddMember("nextDeviceId", nextDeviceId, alloc);
    document.AddMember("devices", rapidjson::Value(rapidjson::kArrayType), alloc);

    for (const auto& [id, device] : devices) {
        rapidjson::Value deviceVal = device->getJsonValue(alloc);
        document["devices"].PushBack(deviceVal, alloc);
    }

    std::ofstream out("save.json");
    
    if (!out.is_open()) {
        std::cout << "FILE_OPEN_ERROR" << std::endl;
        logger.logSaving(false);
        return false;
    }
    
    rapidjson::OStreamWrapper osw(out);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    document.Accept(writer);

    out.close();
    logger.logSaving(true);
    return true;
}

bool DeviceManager::restore() {
    std::ifstream in("save.json");
    
    if (!in.is_open()) {
        std::cout << "FILE_OPEN_ERROR" << std::endl;
        logger.logRestoring(false);
        return false;
    }

    rapidjson::IStreamWrapper isw(in);

    rapidjson::Document document(rapidjson::kObjectType);
    document.ParseStream(isw);
    if (
        document.GetType() != rapidjson::kObjectType ||
        !document.HasMember("nextDeviceId") ||
        !document.HasMember("devices") ||
        document["devices"].GetType() != rapidjson::kArrayType
    ) {
        logger.logRestoring(false);
        return false;
    }

    nextDeviceId = document["nextDeviceId"].GetInt();
    devices.clear();

    for (rapidjson::Value::ConstValueIterator iter = document["devices"].Begin(); iter != document["devices"].End(); ++iter) {
        if (!Device::jsonValueIsValid(*iter)) {
            std::cerr << "The object is damaged" << std::endl;
            continue;
        }

        switch (Device::fromStrDeviceTypeToEnum((*iter)["deviceType"].GetString())) {
            case EDeviceType::GPS_RECEIVER: {
                GPSReceiver d;
                if (!GPSReceiver::tryRestoreFromJsonValue(*iter, d)) {
                    std::cerr << "The object is damaged" << std::endl;
                    continue;
                }

                devices.emplace(d.getId(), std::make_unique<GPSReceiver>(d));
                break;
            }
            case EDeviceType::NETWORK_MONITOR: {
                NetworkMonitor d;
                if (!NetworkMonitor::tryRestoreFromJsonValue(*iter, d)) {
                    std::cerr << "The object is damaged" << std::endl;
                    continue;
                }

                devices.emplace(d.getId(), std::make_unique<NetworkMonitor>(d));
                break;
            }
            case EDeviceType::TEMPERATURE_SENSOR: {
                TemperatureSensor d;
                if (!TemperatureSensor::tryRestoreFromJsonValue(*iter, d)) {
                    std::cerr << "The object is damaged" << std::endl;
                    continue;
                }

                devices.emplace(d.getId(), std::make_unique<TemperatureSensor>(d));
                break;
            }
        }
    }

    logger.logRestoring(true);

    return true;
}