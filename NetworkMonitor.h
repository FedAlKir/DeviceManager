#pragma once

#include "Device.h"

#include<string>

class NetworkMonitor : public Device {
    private:
        int packages;
    
    public:
        NetworkMonitor(const int id, const EDeviceType deviceType, const std::string name);
        ~NetworkMonitor() override = default;

        std::string getDeviceTypeStr() const override { return "NetworkMonitor"; } 

        void tick() override;
        std::string getInfo() const override;
};