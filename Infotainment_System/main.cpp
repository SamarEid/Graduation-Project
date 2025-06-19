#include "UI/MainWindow/mainwindow.h"
#include "UI/Start/startwindow.h"
#include <QApplication>
#include "qdebug.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Communication comm("192.168.189.172", "Infotaiment");
    if (!comm.connect())
    {
        qDebug() << "Failed to connect to MQTT broker!";
        return -1;
    }

    startWindow w(&comm);
    w.show();

    return a.exec();
}
