#include "startwindow.h"
#include "spdlog/spdlog.h"
#include "qdebug.h"
#include "ui_startwindow.h"
#include "UI/MainWindow/mainwindow.h"

startWindow::startWindow(Communication* comm,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startWindow),
    communication(comm)
{
    ui->setupUi(this);
}

startWindow::~startWindow()
{
    delete ui;
}

void startWindow::on_startButton_clicked()
{
    spdlog::info("Start Button Clicked");
    if(communication){
        communication->publishToTopic("actuators", "start");
    }

    //todo: set qos to 2 --> change subscriber first
//    if(communication){
//        auto& client = communication->getClient();
//        auto msg = mqtt::make_message("Car/actuators", "start");
//        msg->set_qos(2);  // Highest QoS
//        client.publish(msg);
//    }
    MainWindow *mainWin = new MainWindow(communication);
       mainWin->show();

    this->close();
}

