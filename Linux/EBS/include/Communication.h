#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <string>
#include "mqtt/async_client.h"

class MQTTCallback : public virtual mqtt::callback {
    public:
        using MessageHandler = std::function<void(mqtt::const_message_ptr)>;
    
        void setMessageHandler(MessageHandler handler);
        void message_arrived(mqtt::const_message_ptr msg) override;
    
    private:
        std::mutex handlerMutex;
        MessageHandler messageHandler;
};

class Communication {
    public:
    Communication(const std::string& broker, const std::string& clientID);
    ~Communication();

    bool connect();
    bool subscribeToTopic(const std::string& topic);
    bool publishToTopic(const std::string& topic,const std::string& message);
    bool disconnect();
    mqtt::async_client& getClient();

    void setMessageHandler(MQTTCallback::MessageHandler handler);

    private:
    std::mutex commMutex; 
    mqtt::async_client client;
    bool connectionStatus;
    MQTTCallback callback; 
};

#endif //COMMUNICATION_H