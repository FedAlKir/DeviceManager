#pragma once

#include "Device.h"

#include<string>

class TemperatureSensor : public Device {
    public:
        TemperatureSensor(const int id, const EDeviceType deviceType, const std::string name);
        ~TemperatureSensor() override = default;
        
        std::string getDeviceTypeStr() const override { return "TemperatureSensor"; }

        void tick() override;
        std::string getInfo() const override;
    
    private:
        float temperature;
};