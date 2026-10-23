#include "NetworkMonitor.h"

#include<string>
#include<sstream>

NetworkMonitor::NetworkMonitor(const int id, const EDeviceType deviceType, const std::string name) :
Device(id, deviceType, name),
packages(0)
{}

void NetworkMonitor::tick() {
    packages += 10;
}

std::string NetworkMonitor::getInfo() const {
    std::stringstream ss;
    ss
    << "ID: " << id << "\n"
    << "Name: " << name << "\n"
    << "Type: " << getDeviceTypeStr() << "\n"
    << "Power: " << getEnabledStr() << "\n"
    << "Packages: " << packages << "\n";
    return ss.str();
}