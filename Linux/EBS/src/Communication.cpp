#include "../include/Communication.h"
#include <iostream>
#include <spdlog/spdlog.h>

void MQTTCallback::setMessageHandler(MessageHandler handler) {
    std::lock_guard<std::mutex> lock(handlerMutex);
    messageHandler = handler;
}

void MQTTCallback::message_arrived(mqtt::const_message_ptr msg) {
    std::lock_guard<std::mutex> lock(handlerMutex);
    if (messageHandler) {
        messageHandler(msg);
    } else {
        spdlog::error("No message handler set! Message ignored.");
    }
}


Communication::Communication(const std::string& broker, const std::string& clientID)
    : client(broker, clientID), connectionStatus(false), callback() {
        client.set_callback(callback);
}

void Communication::setMessageHandler(MQTTCallback::MessageHandler handler) {
    callback.setMessageHandler(handler);
}


Communication::~Communication(){
    disconnect();
}

bool Communication::connect(){
    try{
        mqtt::token_ptr connectionToken = client.connect();
        connectionToken->wait();
        connectionStatus = true;
        spdlog::info("Connected to MQTT broker [{}]",client.get_server_uri());
        return true;
    }
    catch (const mqtt::exception& e) {
        spdlog::error("Failed to connect to broker: {}", e.what());
        return false;
    }
}

mqtt::async_client& Communication::getClient() {
    return client;
}

bool Communication::subscribeToTopic(const std::string& topic){
    if(!connectionStatus){
        spdlog::error("can't subscribe!! NOT CONNECTED TO MQTT BROKER.");
        return false;
    }
    try{
        std::lock_guard<std::mutex> lock(commMutex);  
        client.subscribe(topic, 1)->wait();
        spdlog::info("Subscribed to topic: [{}]", topic);
        return true;
    }
    catch (const mqtt::exception& e){
        // std::cerr << "Failed to subscribe: " << e.what() << std::endl;
        spdlog::error("Failed to subscribe to topic --> [{}] : {}", topic, e.what());
        return false;
    }
}

bool Communication::publishToTopic(const std::string& topic,const std::string& message){
    if(!connectionStatus){
        spdlog::error("Can't publish!! NOT CONNECTED TO BROKER");
        return false;
    }
    try{
        std::lock_guard<std::mutex> lock(commMutex);  
        client.publish(topic,message,1,false);
        spdlog::info("Published to topic --> [{}] : Message: \"{}\"", topic, message);
        return true;
    }
    catch(const mqtt::exception& e){
        spdlog::error("Publishing Failed: {}",e.what());
        return false;
    }
}

bool Communication::disconnect(){
    if(!connectionStatus){
        spdlog::warn("Already disconnected from MQTT broker.");
        return false;
    }
    try{
        client.disconnect()->wait();
        connectionStatus = false;
        spdlog::info("Connection terminated successfully!");
        return true;
    }
    catch(const mqtt::exception& e){
        spdlog::error("Failed to disconnect: {}", e.what());
        return false;
    }
}