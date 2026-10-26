#include "GPSReceiver.h"
#include "rapidjson/document.h"

#include<string>
#include<sstream>

std::string GPSReceiver::getFixState() const {
    if (fixed) return "FIX";
    return "NO_FIX";
}

GPSReceiver::GPSReceiver(const int id, const EDeviceType deviceType, const std::string& name) :
Device(id, deviceType, name),
ticks(0),
fixed(false)
{}

void GPSReceiver::tick() {
    if (!enabled) return;
    if (++ticks == 3) fixed = true;
}

std::string GPSReceiver::getInfo() const {
    std::stringstream ss;
    ss << Device::getInfo()
    << "Fix status: " << getFixState() << "\n"
    << "Ticks: " << ticks << "\n";
    return ss.str();
}

void GPSReceiver::turnOff() {
    ticks = 0;
    fixed = false;
    enabled = false;
}

rapidjson::Value GPSReceiver::getJsonValue(rapidjson::Document::AllocatorType& alloc) const {
    rapidjson::Value v = Device::getJsonValue(alloc);

    v.AddMember("ticks", ticks, alloc);
    v.AddMember("fixed", fixed, alloc);

    return v;
}

bool GPSReceiver::jsonValueIsValid(const rapidjson::Value& val) {
    return (
        Device::jsonValueIsValid(val) &&
        val.HasMember("ticks") &&
        val.HasMember("fixed")
    );
}

bool GPSReceiver::tryRestoreFromJsonValue(const rapidjson::Value& val, GPSReceiver& device) {
    if (
        !Device::tryRestoreFromJsonValue(val, device) ||
        !GPSReceiver::jsonValueIsValid(val)
    ) return false;

    device.ticks = val["ticks"].GetInt();
    device.fixed = val["fixed"].GetBool();

    return true;
}