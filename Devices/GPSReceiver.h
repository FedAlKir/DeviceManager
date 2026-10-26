#pragma once

#include "Device.h"

#include "../external/rapidjson/document.h"

#include<string>

class GPSReceiver : public Device {
    private:
        int ticks;
        bool fixed;

        std::string getFixState() const;
        static void setFixState(const std::string& fixStateStr);
    
    public:
        GPSReceiver() = default;
        GPSReceiver(const int id, const EDeviceType deviceType, const std::string& name);
        ~GPSReceiver() override = default;

        std::string getDeviceTypeStr() const override { return "GPSReceiver"; }

        void tick() override;
        std::string getInfo() const override;
        void turnOff() override;
        
        rapidjson::Value getJsonValue(rapidjson::Document::AllocatorType& alloc) const override;
        static bool jsonValueIsValid(const rapidjson::Value& val);
        static bool tryRestoreFromJsonValue(const rapidjson::Value& val, GPSReceiver& device);
};