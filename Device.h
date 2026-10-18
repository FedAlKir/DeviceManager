#pragma once

#include<string>

struct Device {
    int id;
    std::string name;
    bool enabled;

    Device(int id, std::string name, bool enabled) : id(id), name(name), enabled(enabled) {}
};