#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<memory>

#include "Device.h"

class DeviceManager {
public:
    DeviceManager() = default;
    ~DeviceManager() = default;

    void addDevice(const std::string& name);
    void printAllDevices() const;
    void turnDeviceOn(const int id);
    void turnDeviceOff(const int id);
    Device* findDeviceById(const int id);

private:
    std::vector<std::shared_ptr<Device>> devices;

    bool idIsValid(const int id);
};