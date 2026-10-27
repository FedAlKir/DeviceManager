#pragma once

#include "Device.h"

#include<string>
#include<vector>

class EventLogger {
    private:
        std::vector<std::string> logs;

        void log(std::string logStr);
    
    public:
        void logDeviceAddition(const int id, const Device* const d);
        void logDeviceRemoving(const int id, const Device* const d);
        void logDevicesUpdate();
        void logDeviceActivation(const int id, const Device* const d);
        void logDeviceDeactivation(const int id, const Device* const d);

        void logSaving(const bool success);
        void logRestoring(const bool success);

        void printAllLogs();
};