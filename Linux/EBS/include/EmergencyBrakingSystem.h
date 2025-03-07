#ifndef EMERGENCY_BRAKING_SYSTEM_H
#define EMERGENCY_BRAKING_SYSTEM_H

#include "Communication.h"

class EmergecyBrakingSystem {
    public:
        EmergecyBrakingSystem(Communication &comm, const std::string &sensorTopic, const std::string &alertTopic, 
            double warningThreshold, double criticalThreshold);
        ~EmergecyBrakingSystem();
        void start();
        void message_arrived(mqtt::const_message_ptr msg) ;
    private:
        Communication &comm;
        std::string sensorTopic;
        std::string alertTopic;
        double warningThreshold;
        double criticalThreshold;

        void emergecyBraking(double distance);
};

#endif //EMERGENCY_BRAKING_SYSTEM_H