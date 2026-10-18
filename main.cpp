#include<iostream>
#include<string>
#include<limits>

#include "DeviceManager.h"

std::string stringInput(const std::string& contextLine = "") {
    std::string input;
    std::cout << contextLine;
    std::getline(std::cin, input);
    return input;
}

std::pair<bool, int> int32Input(const std::string& contextLine = "") {
    int value;
    std::cout << contextLine;
    if (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return std::make_pair(false, 0);
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return std::make_pair(true, value);
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
        std::pair<bool, int> inputRes = int32Input(">");
        if (!inputRes.first) {
            std::cout << "Invalid input format!\nEnter a number!\n" << std::endl;
            continue;
        }
        int command = inputRes.second;

        switch (command) {
            case 0: {
                std::cout << "Goodbye!" << std::endl;
                return 0;
            }
            case 1: {
                std::string name = stringInput("Enter name: ");
                deviceManager.addDevice(name);
                break;
            }
            case 2: {
                deviceManager.printAllDevices();
                break;
            }
            case 3: {
                inputRes = int32Input("Enter ID: ");
                if (!inputRes.first) {
                    std::cout << "Invalid input format!\nEnter a number!" << std::endl;
                    break;
                }
                deviceManager.turnDeviceOn(inputRes.second);
                break;
            }
            case 4: {
                inputRes = int32Input("Enter ID: ");
                if (!inputRes.first) {
                    std::cout << "Invalid input format!\nEnter a number!" << std::endl;
                    break;
                }
                deviceManager.turnDeviceOff(inputRes.second);
                break;
            }
            case 5: {
                inputRes = int32Input("Enter ID: ");
                if (!inputRes.first) {
                    std::cout << "Invalid input format!\nEnter a number!" << std::endl;
                    break;
                }
                Device* device = deviceManager.findDeviceById(inputRes.second);
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