#pragma once

#include "Device.h"

#include "rapidjson/document.h"

#include<string>

class TemperatureSensor : public Device {
    public:
        TemperatureSensor() = default;
        TemperatureSensor(const int id, const EDeviceType deviceType, const std::string name);
        ~TemperatureSensor() override = default;
        
        std::string getDeviceTypeStr() const override { return "TemperatureSensor"; }

        void tick() override;
        std::string getInfo() const override;

        rapidjson::Value getJsonValue(rapidjson::Document::AllocatorType& alloc) const override;
        static bool jsonValueIsValid(const rapidjson::Value& val);
        static bool tryRestoreFromJsonValue(const rapidjson::Value& val, TemperatureSensor& device);
    
    private:
        float temperature;
};