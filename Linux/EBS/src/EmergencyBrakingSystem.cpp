#include "../include/EmergencyBrakingSystem.h"
#include "iostream"
#include <spdlog/spdlog.h>


EmergecyBrakingSystem::EmergecyBrakingSystem(Communication &comm, const std::string &sensorTopic, const std::string &alertTopic, std::string &controlTopic,
    double warningThreshold, double criticalThreshold)
    : comm(comm), sensorTopic(sensorTopic), alertTopic(alertTopic),controlTopic(controlTopic), warningThreshold(warningThreshold), criticalThreshold(criticalThreshold){
        spdlog::info("[Debug] BSD instance created --> sensor topic: [{}], alert topic: [{}], warning threshold: [{}], critical threshold: [{}]",
            sensorTopic, alertTopic,controlTopic, warningThreshold, criticalThreshold);
   }

EmergecyBrakingSystem::~EmergecyBrakingSystem(){
    spdlog::info("Unsubscribing from topic: [{}]",sensorTopic);
    if(comm.getClient().is_connected()){
        try{
            comm.getClient().unsubscribe(sensorTopic)->wait();
            comm.getClient().unsubscribe(controlTopic)->wait();
        }
        catch(const mqtt::exception& e){
            spdlog::error("Failed to unsubscribe from topic: [{}] --> {}",sensorTopic, e.what());
        }
    }
    else{
        spdlog::error("Can't unsubscribe!! Not connected to MQTT broker");
    }
}

void EmergecyBrakingSystem::start(){
    comm.subscribeToTopic(sensorTopic);
    comm.subscribeToTopic(controlTopic);
    comm.setMessageHandler([this](mqtt::const_message_ptr msg) {
        this->message_arrived(msg);
    });
}

void EmergecyBrakingSystem::message_arrived(mqtt::const_message_ptr msg){
    if (msg->get_topic() != sensorTopic && msg->get_topic() != controlTopic) return; 
    const std::string& topic = msg->get_topic();
    const std::string& payload = msg->to_string();

    if(topic == sensorTopic){
        if(!ebsON)
            return;
        try{
            double distance = std::stod(msg->to_string());
            spdlog::info("Distance received: [{}]", distance);
            emergecyBraking(distance);
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
   
    if(topic == controlTopic){
        try{
            std::string controlStatus = msg->to_string();
            spdlog::info("message received: [{}]", controlStatus);

            ebsON = (payload == "ON");
        }
        catch(const std::exception& e){
            spdlog::error("Error Parsing the message: {}", e.what());
        }
    }
    
}

void EmergecyBrakingSystem::emergecyBraking(double distance){
    if(distance < criticalThreshold){
        spdlog::critical("Danger!! object detected too close!! >>>> Brake");
        comm.publishToTopic(alertTopic, "DANGER");
    }
    else if(distance < warningThreshold){
        spdlog::warn("Warning!! object detected nearby!!! Slow Down");
        comm.publishToTopic(alertTopic, "WARNING");
    }
    else{
        comm.publishToTopic(alertTopic, "SAFE");
    }
}