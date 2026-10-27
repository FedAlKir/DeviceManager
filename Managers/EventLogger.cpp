#include "EventLogger.h"

#include "Device.h"

#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<ctime>

void EventLogger::log(std::string logStr) {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", localTime);

    std::stringstream ss;
    ss << buffer << " - " << logStr;
    
    logs.push_back(ss.str());
}

void EventLogger::logDeviceAddition(const int id, const Device* const d) {
    std::stringstream ss;
    
    if (d != nullptr) ss << "Device " << d->getName() << ", ID: " << id << " added successfully";
    else ss << "Unsuccessfull attempt of adding device, ID: " << id;

    EventLogger::log(ss.str());
}

void EventLogger::logDeviceRemoving(const int id, const Device* const d) {
    std::stringstream ss;
    
    if (d != nullptr) ss << "Device " << d->getName() << ", ID: " << id << " removed successfully";
    else ss << "Unsuccessfull attempt of removing device, ID: " << id;

    EventLogger::log(ss.str());
}

void EventLogger::logDevicesUpdate() {
    std::stringstream ss;

    ss << "All devices updated";

    EventLogger::log(ss.str());
}

void EventLogger::logDeviceActivation(const int id, const Device* const d) {
    std::stringstream ss;

    if (d != nullptr) ss << "Device " << d->getName() << ", ID: " << id << " turned ON successfully";
    else ss << "Unsuccessfull attempt of turning ON device, ID: " << id;

    EventLogger::log(ss.str());
}

void EventLogger::logDeviceDeactivation(const int id, const Device* const d) {
    std::stringstream ss;

    if (d != nullptr) ss << "Device " << d->getName() << ", ID: " << id << " turned OFF successfully";
    else ss << "Unsuccessfull attempt of turning OFF device, ID: " << id;

    EventLogger::log(ss.str());
}

void EventLogger::logSaving(const bool success) {
    std::stringstream ss;

    if (success) ss << "Devices saved successfully";
    else ss << "Unsuccessfull attempt of saving devices";

    EventLogger::log(ss.str());
}

void EventLogger::logRestoring(const bool success) {
    std::stringstream ss;
    
    if (success) ss << "Devices restored successfully";
    else ss << "Unsuccessfull attempt of restoring devices";

    EventLogger::log(ss.str());
}

void EventLogger::printAllLogs() {
    for (std::string& logStr : logs) std::cout << logStr << std::endl;
}