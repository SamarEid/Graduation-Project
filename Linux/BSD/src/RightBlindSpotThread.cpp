#include "../include/RightBlindSpotThread.h"
#include <iostream>
#include <spdlog/spdlog.h>
#include "../include/ConfigurationManager.h"

void rightBlindSpotThread(Communication &comm){
    spdlog::info("Right blind spot detection thread started");
    ConfigurationManager config("../config.json");
    auto rightBSD = std::make_unique<BlindSpotDetection>(comm, config.RightSensorTopic , config.RightBlindSpotTopic, config.controlTopic, 
                                                                config.warningThreshold , config.criticalThreshold);
    rightBSD->start();

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void startRightBlindSpot(Communication& comm){
    std::thread rightThread(rightBlindSpotThread, std::ref(comm));
    rightThread.detach();
}