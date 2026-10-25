#pragma once

#include<iostream>
#include<map>
#include<string>
#include<memory>

#include "Device.h"
#include "EDeviceType.h"

class DeviceManager {
public:
    DeviceManager();
    ~DeviceManager() = default;

    int addDevice(const EDeviceType deviceType, const std::string& name);
    bool removeDevice(const int id);
    void printAllDevices() const;
    void tickAllDevices();
    bool turnDeviceOn(const int id);
    bool turnDeviceOff(const int id);
    Device* findDeviceById(const int id) const;

    bool save() const;
    bool restore();

private:
    int nextDeviceId;
    std::map<int, std::unique_ptr<Device>> devices;

    bool idIsValid(const int id) const;
};