#ifndef ADAS_NOTIFICATION_H
#define ADAS_NOTIFICATION_H

#include "Communication/Communication.h"
#include "qobject.h"

class ADASNotification : public QObject
{
    Q_OBJECT
public:
    ADASNotification(Communication* comm,QObject* parent = nullptr);
    ~ADASNotification();
    void message_arrived(mqtt::const_message_ptr msg) ;

signals:
    void brakingStatusChanged(const QString& status);
    void rightBlindSpotStatusChanged(const QString& status);
    void leftBlindSpotStatusChanged(const QString& status);
    void trafficSignDetected(const QString& sign);

private:
    Communication* comm;

};

#endif //ADAS_NOTIFICATION_H
