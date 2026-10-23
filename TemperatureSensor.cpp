#include "TemperatureSensor.h"

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
    ss
    << "ID: " << id << "\n"
    << "Name: " << name << "\n"
    << "Type: " << getDeviceTypeStr() << "\n"
    << "Power: " << getEnabledStr() << "\n"
    << "Temperature: " << temperature << " C\n";
    return ss.str();
}