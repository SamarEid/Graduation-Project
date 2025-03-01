cmake_minimum_required(VERSION 3.10)
project(BlindSpotDetection)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find required packages
find_package(spdlog REQUIRED)
find_package(PahoMqttCpp REQUIRED)
find_package(nlohmann_json REQUIRED)

# Add source files
set(SOURCES
    src/main.cpp
    src/Communication.cpp
    src/BlindSpotDetection.cpp
    src/LeftBlindSpotThread.cpp
    src/RightBlindSpotThread.cpp
    src/ConfigurationManager.cpp
)

# Add header files
set(HEADERS
    include/Communication.h
    include/BlindSpotDetection.h
    include/LeftBlindSpotThread.h
    include/RightBlindSpotThread.h
    include/ConfigurationManager.h
)

# Create the executable
add_executable(BlindSpotDetection ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(BlindSpotDetection PRIVATE include)

# Link libraries
target_link_libraries(BlindSpotDetection PRIVATE spdlog::spdlog PahoMqttCpp::paho-mqttpp3 nlohmann_json::nlohmann_json)
