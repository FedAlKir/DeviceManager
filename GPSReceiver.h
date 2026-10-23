#pragma once

#include "Device.h"

#include<string>

class GPSReceiver : public Device {
    private:
        enum EFixState {
            Fix,
            NoFix
        };

        int ticks;
        EFixState fixState;

        std::string getFixState() const;
    
    public:
        GPSReceiver(const int id, const EDeviceType deviceType, const std::string name);
        ~GPSReceiver() override = default;

        std::string getDeviceTypeStr() const override { return "GPSReceiver"; }

        void tick() override;
        std::string getInfo() const override;
        void turnOff() override;
};