cmake_minimum_required(VERSION 3.20)

project(
    DeviceManager
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
    DeviceManager

    main.cpp

    Devices/Device.cpp
    Devices/GPSReceiver.cpp
    Devices/NetworkMonitor.cpp
    Devices/TemperatureSensor.cpp

    Managers/DeviceManager.cpp
)

target_include_directories(
    DeviceManager PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/Devices"
    "${CMAKE_CURRENT_SOURCE_DIR}/Managers"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/rapidjson"
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(
        DeviceManager PRIVATE

        -Wall
        -Wextra
        -Wpedantic
    )
endif()