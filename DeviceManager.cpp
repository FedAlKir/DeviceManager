#include "DeviceManager.h"
#include "Device.h"

#include<iostream>
#include<memory>

bool DeviceManager::idIsValid(const int id) {
    return id <= devices.size() && id >= 1;
}

void DeviceManager::addDevice(const std::string& name) {
    devices.emplace_back(std::make_shared<Device>(Device(
        devices.size() + 1,
        name,
        false
    )));

    std::cout << "Device added! ID: " << devices.size() << std::endl;
}

void DeviceManager::printAllDevices() const {
    for (std::shared_ptr<Device> device : devices) {
        std::string deviceState;
        if (device->enabled) deviceState = "ON";
        else deviceState = "OFF";

        std::cout << "ID: " << device->id << " | " << device->name << " | " << deviceState << std::endl;
    }
}

void DeviceManager::turnDeviceOn(const int id) {
    if (!idIsValid(id)) {
        std::cout << "Device ID invalid" << std::endl;
        return;
    }

    devices[id - 1]->enabled = true;
    std::cout << devices[id - 1]->name << " is now ON" << std::endl;
}

void DeviceManager::turnDeviceOff(const int id) {
    if (!idIsValid(id)) {
        std::cout << "Device ID invalid" << std::endl;
        return;
    }

    devices[id - 1]->enabled = false;
    std::cout << devices[id - 1]->name << " is now OFF" << std::endl;
}

Device* DeviceManager::findDeviceById(const int id) {
    if (!idIsValid(id)) {
        return nullptr;
    }

    return &*devices[id - 1];
}