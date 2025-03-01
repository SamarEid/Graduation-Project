#include "../include/Communication.h"
#include "../include/BlindSpotDetection.h"
#include "../include/LeftBlindSpotThread.h"
#include "../include/RightBlindSpotThread.h"
#include "../include/ConfigurationManager.h"
#include <spdlog/spdlog.h>

// const std::string broker = "tcp://test.mosquitto.org:1883";

int main() {
    ConfigurationManager config("../config.json");
    Communication leftComm(config.broker, config.LeftClientId);
    Communication rightComm(config.broker, config.RightClientId);
    
    if (!leftComm.connect()) return -1;
    if (!rightComm.connect()) return -1;

    startLeftBlindSpot(leftComm);
    startRightBlindSpot(rightComm);
    
    spdlog::info("Blind spot detection running. Press Ctrl+C to exit.");

    // Keep the main thread alive
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
