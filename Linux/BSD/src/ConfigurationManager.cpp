#include "../include/ConfigurationManager.h"
#include <fstream>

ConfigurationManager::ConfigurationManager(const std::string& configFilePath){
    load(configFilePath);
}

void ConfigurationManager::load(const std::string& configFilePath){
    std::ifstream configFile(configFilePath);
    if(!configFile.is_open()){
        spdlog::critical("Config file [{}] not found! App cann't start",configFilePath);
    }
    json configJson;
    configFile >> configJson;

    broker = configJson["mqtt"]["broker"];
    LeftClientId = configJson["mqtt"]["client_id_left"];
    RightClientId = configJson["mqtt"]["client_id_right"];
    LeftSensorTopic = configJson["mqtt"]["left_sensor_topic"];
    RightSensorTopic = configJson["mqtt"]["right_sensor_topic"];
    RightBlindSpotTopic = configJson["mqtt"]["right_alert_topic"];
    LeftBlindSpotTopic = configJson["mqtt"]["left_alert_topic"];
    controlTopic = configJson["mqtt"]["control"];
    criticalThreshold = configJson["thresholds"]["critical_threshold"];
    warningThreshold = configJson["thresholds"]["warning_threshold"];
}