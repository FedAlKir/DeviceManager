#include<iostream>
#include<utility>
#include<string>
#include<sstream>
#include<vector>

#include "Managers/DeviceManager.h"

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

    const std::vector<std::pair<std::string, EDeviceType>> deviceTypes = {
        { "Temperature sensor", EDeviceType::TEMPERATURE_SENSOR },
        { "GPS receiver", EDeviceType::GPS_RECEIVER },
        { "Network monitor", EDeviceType::NETWORK_MONITOR }
    };

    DeviceManager deviceManager;

    std::cout << "=== Device Manager ===\n\n"
    << "1. Add device\n"
    << "2. Show all devices\n"
    << "3. Turn device ON\n"
    << "4. Turn device OFF\n"
    << "5. Update all devices (Tick)\n"
    << "6. Find device by ID\n"
    << "7. Remove device\n"
    << "8. Save data\n"
    << "9. Restore data\n"
    << "10. Print all logs\n"
    << "0. Exit\n"
    << std::endl;

    while (true) {
        int command;
        InputStatus inputStatus = int32Input(">", command);
        std::cout << "\n";
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

                std::stringstream ss;
                ss << "Enter a device type number:\n";
                for (size_t i = 0; i < deviceTypes.size(); ++i) {
                    ss << (i + 1) << ". " << deviceTypes[i].first << "\n";
                }

                int deviceTypeId;
                inputStatus = int32Input(ss.str(), deviceTypeId);

                if (inputStatus == InputStatus::Eof) return 0;
                else if (inputStatus == InputStatus::Invalid) {
                    std::cout << "Invalid input format!\nEnter a number!" << std::endl;
                    break;
                }

                std::cout << "Device added! ID: "
                << deviceManager.addDevice(deviceTypes[deviceTypeId - 1].second, name) << std::endl;
                break;
            }
            case 2: {
                deviceManager.printAllDevices();
                break;
            }
            case 3: {
                int id;
                inputStatus = int32Input("Enter ID: ", id);
                if (inputStatus == InputStatus::Eof) return 0;
                else if (inputStatus == InputStatus::Invalid) {
                    std::cout << "Invalid input format!\nEnter a number!" << std::endl;
                    break;
                }
                if (!deviceManager.turnDeviceOn(id)) std::cout << "Device ID invalid" << std::endl;
                break;
            }
            case 4: {
                int id;
                inputStatus = int32Input("Enter ID: ", id);
                if (inputStatus == InputStatus::Eof) return 0;
                else if (inputStatus == InputStatus::Invalid) {
                    std::cout << "Invalid input format!\nEnter a number!" << std::endl;
                    break;
                }
                if (!deviceManager.turnDeviceOff(id)) std::cout << "Device ID invalid" << std::endl;
                break;
            }
            case 5: {
                deviceManager.tickAllDevices();
                std::cout << "All devices updated!" << std::endl;
                break;
            }
            case 6: {
                int id;
                inputStatus = int32Input("Enter ID: ", id);

                if (inputStatus == InputStatus::Eof) return 0;
                if (inputStatus == InputStatus::Invalid) {
                    std::cout << "Invalid input format!\nEnter a number!" << std::endl;
                    break;
                }

                const Device* device = deviceManager.findDeviceById(id);
                if (device == nullptr) {
                    std::cout << "Device not found!" << std::endl;
                    break;
                }

                std::cout << device->getInfo() << std::endl;
                break;
            }
            case 7: {
                int id;
                inputStatus = int32Input("Enter ID: ", id);

                if (inputStatus == InputStatus::Eof) return 0;
                if (inputStatus == InputStatus::Invalid) {
                    std::cout << "Invalid input format!\nEnter a number!" << std::endl;
                    break;
                }

                if (!deviceManager.removeDevice(id)) {
                    std::cout << "Device not found!" << std::endl;
                }
                else {
                    std::cout << "Device deleted successfuly!" << std::endl;
                }

                break;
            }
            case 8: {
                if (!deviceManager.save()) {
                    std::cout << "Devices backup failed" << std::endl;
                }
                else {
                    std::cout << "Devices saved successfully" << std::endl;
                }
                break;
            }
            case 9: {
                if (!deviceManager.restore()) {
                    std::cout << "Devices restore failed" << std::endl;
                }
                else {
                    std::cout << "Devices restored successfully" << std::endl;
                }
                break;
            }
            case 10: {
                deviceManager.printAllLogs();
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