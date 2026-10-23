#include "DeviceManager.h"

#include "Device.h"
#include "EDeviceType.h"
#include "TemperatureSensor.h"
#include "GPSReceiver.h"
#include "NetworkMonitor.h"

#include<iostream>
#include<memory>

bool DeviceManager::idIsValid(const int id) const {
    return devices.find(id) != devices.end();
}

DeviceManager::DeviceManager() : nextDeviceId(1) {}

int DeviceManager::addDevice(const EDeviceType deviceType, const std::string& name) {
    switch (deviceType) {
        case EDeviceType::TEMPERATURE_SENSOR: {
            devices[nextDeviceId++] = std::make_unique<TemperatureSensor>(
                nextDeviceId,
                deviceType,
                name
            );
            break;
        }
        case EDeviceType::GPS_RECEIVER: {
            devices[nextDeviceId++] = std::make_unique<GPSReceiver>(
                nextDeviceId,
                deviceType,
                name
            );
            break;
        }
        case EDeviceType::NETWORK_MONITOR: {
            devices[nextDeviceId++] = std::make_unique<NetworkMonitor>(
                nextDeviceId,
                deviceType,
                name
            );
            break;
        }
        default: {
            std::cerr << "UNKNOWN_DEVICE_TYPE_ERROR" << std::endl;
        }
    }

    return nextDeviceId - 1;
}

bool DeviceManager::removeDevice(const int id) {
    if (!idIsValid(id)) return false;

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
}

bool DeviceManager::turnDeviceOn(const int id) {
    if (!idIsValid(id)) return false;

    devices[id]->turnOn();
    std::cout << devices[id]->getName() << " is now ON" << std::endl;
    return true;
}

bool DeviceManager::turnDeviceOff(const int id) {
    if (!idIsValid(id)) return false;

    devices[id]->turnOff();
    std::cout << devices[id]->getName() << " is now OFF" << std::endl;
    return true;
}

Device* DeviceManager::findDeviceById(const int id) const {
    if (!idIsValid(id)) {
        return nullptr;
    }

    return devices.find(id)->second.get();
}