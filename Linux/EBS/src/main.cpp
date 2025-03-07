#include "../include/Communication.h"
#include "../include/EmergencyBrakingSystem.h"
#include "../include/ConfigurationManager.h"
#include <spdlog/spdlog.h>

int main(){
    ConfigurationManager config("../config.json");
    Communication ebs_comm(config.broker, config.ClientId);
    EmergecyBrakingSystem ebs(ebs_comm, config.frontSensorTopic, config.emergencyBrakingInfo, config.warningThreshold, config.criticalThreshold);

    if(!ebs_comm.connect())
        return -1;
    ebs.start();
    spdlog::info("Emergency Braking System running. Press Ctrl+C to exit.");
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}