#include "NetworkMonitor.h"

#include "rapidjson/document.h"

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
    ss << Device::getInfo()
    << "Packages: " << packages << "\n";
    return ss.str();
}


rapidjson::Value NetworkMonitor::getJsonValue(rapidjson::Document::AllocatorType& alloc) const {
    rapidjson::Value v = Device::getJsonValue(alloc);

    v.AddMember("packages", packages, alloc);

    return v;
}

bool NetworkMonitor::jsonValueIsValid(const rapidjson::Value& val) {
    return (
        Device::jsonValueIsValid(val) &&
        val.HasMember("packages")
    );
}

bool NetworkMonitor::tryRestoreFromJsonValue(const rapidjson::Value& val, NetworkMonitor& device) {
    if (
        !Device::tryRestoreFromJsonValue(val, device) ||
        !NetworkMonitor::jsonValueIsValid(val)
    ) return false;

    device.packages = val["packages"].GetInt();

    return true;
}