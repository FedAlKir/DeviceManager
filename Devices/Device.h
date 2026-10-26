#pragma once

#include "EDeviceType.h"
#include "../external/rapidjson/document.h"

#include<string>
#include<sstream>

class Device {
    public:
        Device() = default;
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
        virtual std::string getInfo() const;
        virtual void turnOn() { enabled = true; }
        virtual void turnOff() { enabled = false; }

        static EDeviceType fromStrDeviceTypeToEnum(const char* deviceType);

        virtual rapidjson::Value getJsonValue(rapidjson::Document::AllocatorType& alloc) const;
        static bool jsonValueIsValid(const rapidjson::Value& val);
        static bool tryRestoreFromJsonValue(const rapidjson::Value& val, Device& device);
    
    protected:
        int id;
        EDeviceType deviceType;
        std::string name;
        bool enabled;
        
        std::string getEnabledStr() const;

};