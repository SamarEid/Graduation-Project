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
    ClientId = configJson["mqtt"]["client_id"];
    frontSensorTopic = configJson["mqtt"]["front_sensor_topic"];
    emergencyBrakingInfo = configJson["mqtt"]["front_alert_topic"];
    criticalThreshold = configJson["thresholds"]["critical_threshold"];
    warningThreshold = configJson["thresholds"]["warning_threshold"];
}