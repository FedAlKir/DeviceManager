#include<iostream>
#include<string>
#include<sstream>
#include<stdexcept>

#include "DeviceManager.h"

enum class InputStatus {
    Ok,
    Invalid,
    Eof
};

InputStatus stringInput(const std::string& contextLine, std::string& input) {
    std::cout << contextLine;
    if (!std::getline(std::cin, input)) {
        if (std::cin.eof()) return InputStatus::Eof;
        else throw std::runtime_error("Input stream error");
    }
    return InputStatus::Ok;
}

InputStatus int32Input(const std::string& contextLine, int& value) {
    std::string input;
    if (stringInput(contextLine, input) != InputStatus::Ok) {
        return InputStatus::Eof;
    }

    std::istringstream stream(input);
    char extra;

    if (!(stream >> value) || (stream >> extra)) {
        return InputStatus::Invalid;
    }

    return InputStatus::Ok;
}

int main() {

    DeviceManager deviceManager;

    std::cout << "=== Device Manager ===\n\n"
    << "1. Add device\n"
    << "2. Show devices\n"
    << "3. Turn on device\n"
    << "4. Turn off device\n"
    << "5. Find device\n"
    << "0. Exit\n" << std::endl;

    while (true) {
        int command;
        InputStatus inputStatus = int32Input(">", command);
        if (inputStatus == InputStatus::Invalid) {
            std::cout << "Invalid input format!\nEnter a number!\n" << std::endl;
            continue;
        }
        if (inputStatus == InputStatus::Eof) command = 0;

        switch (command) {
            case 0: {
                std::cout << "Goodbye!" << std::endl;
                return 0;
            }
            case 1: {
                std::string name;
                inputStatus = stringInput("Enter name: ", name);
                if (inputStatus == InputStatus::Eof) return 0;
                if (name == "") {
                    std::cout << "Device name cannot be empty!" << std::endl;
                    break;
                }
                std::cout << "Device added! ID: " << deviceManager.addDevice(name) << std::endl;
                break;
            }
            case 2: {
                deviceManager.printAllDevices();
                break;
            }
            case 3: {
                int id;
                inputStatus = int32Input("Enter ID: ", id);
                if (inputStatus == InputStatus::Invalid) {
                    std::cout << "Invalid input format!\nEnter a number!" << std::endl;
                    break;
                }
                if (inputStatus == InputStatus::Eof) return 0;
                deviceManager.turnDeviceOn(id);
                break;
            }
            case 4: {
                int id;
                inputStatus = int32Input("Enter ID: ", id);
                if (inputStatus == InputStatus::Invalid) {
                    std::cout << "Invalid input format!\nEnter a number!" << std::endl;
                    break;
                }
                if (inputStatus == InputStatus::Eof) return 0;
                deviceManager.turnDeviceOff(id);
                break;
            }
            case 5: {
                int id;
                inputStatus = int32Input("Enter ID: ", id);
                if (inputStatus == InputStatus::Invalid) {
                    std::cout << "Invalid input format!\nEnter a number!" << std::endl;
                    break;
                }
                if (inputStatus == InputStatus::Eof) return 0;
                Device* device = deviceManager.findDeviceById(id);
                if (device == nullptr) {
                    std::cout << "Device not found!" << std::endl;
                    break;
                }
                std::string deviceState;
                if (device->enabled) deviceState = "ON";
                else deviceState = "OFF";

                std::cout << "ID: " << device->id << " | " << device->name << " | " << deviceState << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid command" << std::endl;
                break;
            }
        }
        std::cout << std::endl;
    }

    return 0;
}