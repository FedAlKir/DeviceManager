#pragma once

#include "Device.h"

#include "rapidjson/document.h"

#include<string>

class NetworkMonitor : public Device {
    private:
        int packages;
    
    public:
        NetworkMonitor() = default;
        NetworkMonitor(const int id, const EDeviceType deviceType, const std::string name);
        ~NetworkMonitor() override = default;

        std::string getDeviceTypeStr() const override { return "NetworkMonitor"; } 

        void tick() override;
        std::string getInfo() const override;

        rapidjson::Value getJsonValue(rapidjson::Document::AllocatorType& alloc) const override;
        static bool jsonValueIsValid(const rapidjson::Value& val);
        static bool tryRestoreFromJsonValue(const rapidjson::Value& val, NetworkMonitor& device);
};