#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

#include <string>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

using json = nlohmann::json;

class ConfigurationManager{
    public:
        std::string broker;
        std::string ClientId;
        std::string frontSensorTopic;
        std::string emergencyBrakingInfo;
        std::string controlTopic;
        double criticalThreshold;
        double warningThreshold;

        ConfigurationManager(const std::string& configFilePath);
        void load(const std::string& configFilePath);
};

#endif // CONFIGURATION_MAHANER_H