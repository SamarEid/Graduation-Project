#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

#include <string>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

using json = nlohmann::json;

class ConfigurationManager{
    public:
        std::string broker;
        std::string LeftClientId;
        std::string RightClientId;
        std::string RightSensorTopic;
        std::string LeftSensorTopic;
        std::string RightBlindSpotTopic;
        std::string LeftBlindSpotTopic;
        double criticalThreshold;
        double warningThreshold;

        ConfigurationManager(const std::string& configFilePath);
        void load(const std::string& configFilePath);
};

#endif // CONFIGURATION_MAHANER_H