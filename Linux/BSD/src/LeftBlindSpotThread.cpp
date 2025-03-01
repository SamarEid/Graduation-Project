#include "../include/LeftBlindSpotThread.h"
#include "../include/ConfigurationManager.h"
#include <iostream>
#include <spdlog/spdlog.h>

void leftBlindSpotThread(Communication &comm){
    spdlog::info("left blind spot detection started");
    ConfigurationManager config("../config.json");
    auto leftBSD = std::make_unique<BlindSpotDetection>(comm,config.LeftSensorTopic, config.LeftBlindSpotTopic,
                                                         config.warningThreshold, config.criticalThreshold);
    leftBSD->start();

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void startLeftBlindSpot(Communication& comm){
    std::thread leftThread(leftBlindSpotThread, std::ref(comm));
    leftThread.detach();
}