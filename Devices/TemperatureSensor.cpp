#include "TemperatureSensor.h"

#include "../external/rapidjson/document.h"

#include<string>
#include<sstream>

TemperatureSensor::TemperatureSensor(const int id, const EDeviceType deviceType, const std::string name) :
Device(id, deviceType, name),
temperature(20.0f)
{}

void TemperatureSensor::tick() {
    temperature += 0.5f;
    if (temperature > 30.0f) temperature = 20.0f;
}

std::string TemperatureSensor::getInfo() const {
    std::stringstream ss;
    ss << Device::getInfo()
    << "Temperature: " << temperature << " C\n";
    return ss.str();
}

rapidjson::Value TemperatureSensor::getJsonValue(rapidjson::Document::AllocatorType& alloc) const {
    rapidjson::Value v = Device::getJsonValue(alloc);

    v.AddMember("temperature", temperature, alloc);

    return v;
}

bool TemperatureSensor::jsonValueIsValid(const rapidjson::Value& val) {
    return (
        Device::jsonValueIsValid(val) &&
        val.HasMember("temperature")
    );
}

bool TemperatureSensor::tryRestoreFromJsonValue(const rapidjson::Value& val, TemperatureSensor& device) {
    if (
        !Device::tryRestoreFromJsonValue(val, device) ||
        !TemperatureSensor::jsonValueIsValid(val)
    ) return false;

    device.temperature = val["temperature"].GetFloat();

    return true;
}