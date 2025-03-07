cmake_minimum_required(VERSION 3.10)
project(EmergencyBrakingSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Check if we are cross-compiling
if(CMAKE_CROSSCOMPILING)
    message(STATUS "Cross-compiling for Raspberry Pi")
else()
    message(STATUS "Building natively")
endif()

# Find required packages
find_package(spdlog REQUIRED)
find_package(PahoMqttCpp REQUIRED)
find_package(nlohmann_json REQUIRED)

# Add source files
set(SOURCES
    src/main.cpp
    src/Communication.cpp
    src/EmergencyBrakingSystem.cpp
    src/ConfigurationManager.cpp
)

# Add header files
set(HEADERS
    include/Communication.h
    include/EmergencyBrakingSystem.h
    include/ConfigurationManager.h
)

# Create the executable
add_executable(EmergencyBrakingSystem ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(EmergencyBrakingSystem PRIVATE include)

# Link libraries
target_link_libraries(EmergencyBrakingSystem PRIVATE spdlog::spdlog PahoMqttCpp::paho-mqttpp3 nlohmann_json::nlohmann_json)
