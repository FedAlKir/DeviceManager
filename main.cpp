#include<iostream>
#include<string>

#include "DeviceManager.h"

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
        std::cout << "> ";
        std::cin >> command;

        switch (command) {
            case 0: {
                std::cout << "Goodbye!" << std::endl;
                return 0;
            }
            case 1: {
                std::string name;
                std::cout << "Enter name: ";
                std::cin >> name;
                deviceManager.addDevice(name);
                break;
            }
            case 2: {
                deviceManager.printAllDevices();
                break;
            }
            case 3: {
                int id;
                std::cout << "Enter ID: ";
                std::cin >> id;
                deviceManager.turnDeviceOn(id);
                break;
            }
            case 4: {
                int id;
                std::cout << "Enter ID: ";
                std::cin >> id;
                deviceManager.turnDeviceOff(id);
                break;
            }
            case 5: {
                int id;
                std::cout << "Enter ID: ";
                std::cin >> id;
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