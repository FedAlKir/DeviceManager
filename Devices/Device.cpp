#include "Device.h"

#include "rapidjson/document.h"

#include<string>
#include<cstring>
#include<sstream>

EDeviceType Device::fromStrDeviceTypeToEnum(const char* deviceType) {
    if (strcmp(deviceType, "GPSReceiver") == 0) return EDeviceType::GPS_RECEIVER;
    if (strcmp(deviceType, "NetworkMonitor") == 0) return EDeviceType::NETWORK_MONITOR;
    return EDeviceType::TEMPERATURE_SENSOR;
}

std::string Device::getEnabledStr() const {
    if (enabled) return "ON";
    return "OFF";
}

std::string Device::getInfo() const {
    std::stringstream ss;
    ss
    << "ID: " << id << "\n"
    << "Name: " << name << "\n"
    << "Type: " << getDeviceTypeStr() << "\n"
    << "Power: " << getEnabledStr() << "\n";
    return ss.str();
}

rapidjson::Value Device::getJsonValue(rapidjson::Document::AllocatorType& alloc) const {
    rapidjson::Value v(rapidjson::kObjectType);

    v.AddMember("id", id, alloc);
    v.AddMember("deviceType", rapidjson::Value(getDeviceTypeStr().c_str(), alloc), alloc);
    v.AddMember("name", rapidjson::Value(name.c_str(), alloc), alloc);
    v.AddMember("enabled", enabled, alloc);

    return v;
}

bool Device::jsonValueIsValid(const rapidjson::Value& val) {
    return (
        val.HasMember("id") &&
        val.HasMember("deviceType") &&
        val.HasMember("name") &&
        val.HasMember("enabled")
    );
}

bool Device::tryRestoreFromJsonValue(const rapidjson::Value& val, Device& device) {
    if (!jsonValueIsValid(val)) return false;

    device.id = val["id"].GetInt();
    device.deviceType = fromStrDeviceTypeToEnum(val["deviceType"].GetString());
    device.name = val["name"].GetString();
    device.enabled = val["enabled"].GetBool();

    return true;
}