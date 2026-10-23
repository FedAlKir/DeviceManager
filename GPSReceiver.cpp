#include "GPSReceiver.h"

#include<string>
#include<sstream>

std::string GPSReceiver::getFixState() const {
    if (fixState == EFixState::Fix) return "FIX";
    return "NO_FIX";
}

GPSReceiver::GPSReceiver(const int id, const EDeviceType deviceType, const std::string name) :
Device(id, deviceType, name),
ticks(0),
fixState(EFixState::NoFix)
{}

void GPSReceiver::tick() {
    if (!enabled) return;
    if (++ticks == 3) fixState = EFixState::Fix;
}

std::string GPSReceiver::getInfo() const {
    std::stringstream ss;
    ss
    << "ID: " << id << "\n"
    << "Name: " << name << "\n"
    << "Type: " << getDeviceTypeStr() << "\n"
    << "Power: " << getEnabledStr() << "\n"
    << "Fix status: " << getFixState() << "\n"
    << "Ticks: " << ticks << "\n";
    return ss.str();
}

void GPSReceiver::turnOff() {
    ticks = 0;
    fixState = EFixState::NoFix;
    enabled = false;
}