#pragma once

#include "EDeviceType.h"

#include<string>

class Device {
    public:
        Device(const int id, const EDeviceType deviceType, const std::string name) : 
        id(id), 
        deviceType(deviceType), 
        name(name), 
        enabled(false) 
        {}
        
        virtual ~Device() = default;

        int getId() const { return id; }
        EDeviceType getDeviceType() const { return deviceType; }
        virtual std::string getDeviceTypeStr() const = 0;
        std::string getName() const { return name; }
        bool isEnabled() const { return enabled; }

        virtual void tick() = 0;
        virtual std::string getInfo() const = 0;
        virtual void turnOn() { enabled = true; }
        virtual void turnOff() { enabled = false; }
    
    protected:
        int id;
        EDeviceType deviceType;
        std::string name;
        bool enabled;
        
        std::string getEnabledStr() const {
            if (enabled) return "ON";
            return "OFF";
        }

};