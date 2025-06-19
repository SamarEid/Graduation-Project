#ifndef BLINDSPOTDETECTION_H
#define BLINDSPOTDETECTION_H

#include "Communication.h"

class BlindSpotDetection {
    public:
        BlindSpotDetection(Communication &comm, const std::string &sensorTopic, const std::string &alertTopic, const std::string &controlTopic,
            double warningThreshold, double criticalThreshold);
        ~BlindSpotDetection();
        void start();
        void message_arrived(mqtt::const_message_ptr msg) ;
    private:
        Communication &comm;
        std::string sensorTopic;
        std::string alertTopic;
        std::string controlTopic;
        double warningThreshold;
        double criticalThreshold;
        bool bsdON = true;

        void checkBlindSpot(double distance);
};

#endif //BLINDSPOTDETECTION_H