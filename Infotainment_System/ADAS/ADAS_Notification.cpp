#include "ADAS_Notification.h"
#include "spdlog/spdlog.h"
#include <string>
#include "iostream"
#include "QObject"

ADASNotification::ADASNotification(Communication *comm,QObject *parent)
    :QObject(parent),comm(comm){
    if(comm){
        comm->subscribeToTopic("info/braking");
        comm->subscribeToTopic("info/bsd/left");
        comm->subscribeToTopic("info/bsd/right");
        comm->subscribeToTopic("info/tsr");
        comm->setMessageHandler([this](mqtt::const_message_ptr msg)
        {
                this->message_arrived(msg);
        });
    }
}
ADASNotification::~ADASNotification(){

}
void ADASNotification::message_arrived(mqtt::const_message_ptr msg){
    if (msg->get_topic() == "info/braking"){
        try{
            std::string info = msg->to_string();
            spdlog::info("message received on topic [{}] : [{}]",msg->get_topic(), info);
            emit brakingStatusChanged(QString::fromStdString(info));
        }
        catch(const std::exception& e){
            spdlog::error("Error Parsing the message: {}", e.what());
        }
    }
    else if(msg->get_topic() == "info/bsd/left"){
        try{
            std::string info = msg->to_string();
            spdlog::info("message received on topic [{}] : [{}]",msg->get_topic(), info);
            emit leftBlindSpotStatusChanged(QString::fromStdString(info));
        }
        catch(const std::exception& e){
            spdlog::error("Error Parsing the message: {}", e.what());
        }
    }
    else if(msg->get_topic() == "info/bsd/right"){
        try{
            std::string info = msg->to_string();
            spdlog::info("message received on topic [{}] : [{}]",msg->get_topic(), info);
            emit rightBlindSpotStatusChanged(QString::fromStdString(info));
        }
        catch(const std::exception& e){
            spdlog::error("Error Parsing the message: {}", e.what());
        }
    }
    else if(msg->get_topic() == "info/tsr"){
        try{
            std::string info = msg->to_string();
            spdlog::info("message received on topic [{}] : [{}]",msg->get_topic(), info);
            emit trafficSignDetected(QString::fromStdString(info));
        }
        catch(const std::exception& e){
            spdlog::error("Error parsing the message: {}",e.what());
        }
    }
    else
        return;

}
