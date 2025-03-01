#include "../include/BlindSpotDetection.h"
#include "iostream"
#include <spdlog/spdlog.h>


BlindSpotDetection::BlindSpotDetection(Communication &comm, const std::string &sensorTopic, const std::string &alertTopic, 
    double warningThreshold, double criticalThreshold)
    : comm(comm), sensorTopic(sensorTopic), alertTopic(alertTopic), warningThreshold(warningThreshold), criticalThreshold(criticalThreshold){
        spdlog::info("[Debug] BSD instance created --> sensor topic: [{}], alert topic: [{}], warning threshold: [{}], critical threshold: [{}]",
            sensorTopic, alertTopic, warningThreshold, criticalThreshold);
   }

BlindSpotDetection::~BlindSpotDetection(){
    spdlog::info("Unsubscribing from topic: [{}]",sensorTopic);
    if(comm.getClient().is_connected()){
        try{
            comm.getClient().unsubscribe(sensorTopic)->wait();
        }
        catch(const mqtt::exception& e){
            spdlog::error("Failed to unsubscribe from topic: [{}] --> {}",sensorTopic, e.what());
        }
    }
    else{
        spdlog::error("Can't unsubscribe!! Not connected to MQTT broker");
    }
}

void BlindSpotDetection::start(){
    comm.subscribeToTopic(sensorTopic);
    comm.setMessageHandler([this](mqtt::const_message_ptr msg) {
        this->message_arrived(msg);
    });
}

void BlindSpotDetection::message_arrived(mqtt::const_message_ptr msg){
    if (msg->get_topic() != sensorTopic) return; 
    try{
        double distance = std::stod(msg->to_string());
        spdlog::info("Distance received: [{}]", distance);
        checkBlindSpot(distance);
    }
    catch(const std::invalid_argument&){
        spdlog::error("Invalid distance format received: {}",msg->to_string());
    }
    catch(const std::out_of_range&){
        spdlog::error("Distance value out of range: {}",msg->to_string());
    }
    catch(const std::exception& e){
        spdlog::error("Error Parsing the message: {}", e.what());
    }
}

void BlindSpotDetection::checkBlindSpot(double distance){
    if(distance < criticalThreshold){
        spdlog::critical("Danger!! object detected too close!");
        comm.publishToTopic(alertTopic, "DANGER");
    }
    else if(distance < warningThreshold){
        spdlog::warn("Warning!! object detected nearby");
        comm.publishToTopic(alertTopic, "WARNING");
    }
    else{
        comm.publishToTopic(alertTopic, "SAFE");
    }
}