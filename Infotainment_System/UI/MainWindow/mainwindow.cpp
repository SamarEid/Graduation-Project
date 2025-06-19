#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"
#include <QTimer>
#include <QResizeEvent>
#include "spdlog/spdlog.h"

MainWindow::MainWindow(Communication* comm,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), communication(comm)
{
    ui->setupUi(this);

    // ADAS Notificaitons
    // Emergency Braking Label
    brakingStatusLabel = new QLabel(ui->centralwidget);
    brakingStatusLabel->setAlignment(Qt::AlignCenter);
    brakingStatusLabel->setGeometry(200, 30, 500, 80);
    brakingStatusLabel->setStyleSheet("font-size: 24px; color: white; background-color: transparent;");
    brakingStatusLabel->hide();
    notification = new ADASNotification(communication, this);
    connect(notification, &ADASNotification::brakingStatusChanged,
            this, &MainWindow::updateBrakingStatus);

    // Left Blind Spot Label
    leftBlindSpotLabel = new QLabel(ui->centralwidget);
    leftBlindSpotLabel->setAlignment(Qt::AlignCenter);
    leftBlindSpotLabel->setStyleSheet("font-size: 24px; color: white; background-color: transparent;");
    leftBlindSpotLabel->setGeometry(200, 140, 500, 80);
    leftBlindSpotLabel->hide(); // Hide by default
    connect(notification, &ADASNotification::leftBlindSpotStatusChanged,
            this, &MainWindow::updateLeftBlindSpotStatus);

    // Right Blind Spot Label
    rightBlindSpotLabel = new QLabel(ui->centralwidget);
    rightBlindSpotLabel->setAlignment(Qt::AlignCenter);
    rightBlindSpotLabel->setStyleSheet("font-size: 24px; color: white; background-color: transparent;");
    rightBlindSpotLabel->setGeometry(200, 250, 500, 80);
    rightBlindSpotLabel->hide(); // Hide by default
    connect(notification,&ADASNotification::rightBlindSpotStatusChanged,
            this,&MainWindow::updateRightBlindSpotStatus);

    // Traffic Sign Label
    trafficSignLabel = new QLabel(ui->centralwidget);
    trafficSignLabel->setAlignment(Qt::AlignCenter);
    trafficSignLabel->setStyleSheet("font-size: 24px; color: white; background-color: transparent;");
    trafficSignLabel->setGeometry(200, 360, 500, 80);
    trafficSignLabel->hide(); // Hide by default
    trafficSign = new QLabel(ui->centralwidget);
    trafficSign->setAlignment(Qt::AlignCenter);
    trafficSign->setStyleSheet("font-size: 24px; color: white; background-color: transparent;");
    trafficSign->setGeometry(290, 360, 400, 80);
    trafficSign->hide(); // Hide by default
    connect(notification,&ADASNotification::trafficSignDetected,
            this,&MainWindow::displayTrafficSign);
    tsrTimer = new QTimer(this);
    tsrTimer->setSingleShot(true);

    connect(tsrTimer, &QTimer::timeout, this, [=]() {
        trafficSign->hide();
        trafficSignLabel->hide();
    });

    // Side Panel
    sidePanel = new QWidget(ui->centralwidget);
    sidePanel->setGeometry(0, 0, 100, height()); // Fixed width panel
    sidePanel->setStyleSheet("background-color: #2c3e50;"); // Dark background

    //Settings button
    settingsButton = new QPushButton(QIcon(":/image/settings.png"), "", sidePanel);
    settingsButton->setIconSize(QSize(70, 70));
    settingsButton->setFixedSize(60, 60);
    settingsButton->setStyleSheet("padding: 0px; border: none;");
    settingsButton->setGeometry(20, 20, 60, 60); // Position and size
    settingsButton->setStyleSheet("background-color: #2c3e50;");
    connect(settingsButton, &QPushButton::clicked, this, &MainWindow::onSettingsButtonClicked);

    // Settings Panel
    settingsPanel = new QWidget(ui->centralwidget);
    settingsPanel->setGeometry(100,0,400,height());
    settingsPanel->setStyleSheet("background-color: #f5f5f5;");
    settingsPanel->hide();
    // ADAS Control Title
    adasControlLabel = new QLabel("ADAS Control", settingsPanel);
    adasControlLabel->setGeometry(20, 20, 300, 40);
    adasControlLabel->setStyleSheet("font-size: 22px; font-weight: bold; color: #2c3e50;");
    QFrame* titleLine = new QFrame(settingsPanel);
    titleLine->setGeometry(20, 60, 360, 2);
    titleLine->setFrameShape(QFrame::HLine);
    titleLine->setFrameShadow(QFrame::Sunken);

    // EBS Control
    ebsLabel = new QLabel("Emergency Braking", settingsPanel);
    ebsLabel->setGeometry(20, 80, 200, 40);
    ebsLabel->setStyleSheet("font-size: 18px; color: #2c3e50;");
    ebsSwitch = new QCheckBox(settingsPanel);
    ebsSwitch->setGeometry(200, 80, 100, 30);
    ebsSwitch->setStyleSheet(R"( QCheckBox::indicator {width: 100px;height: 50px;}
                                 QCheckBox::indicator:unchecked {image: url(:/image/off-button.png);}
                                 QCheckBox::indicator:checked {image: url(:/image/switch-on.png);})");
    ebsSwitch->setChecked(true);
    connect(ebsSwitch, &QCheckBox::toggled, this, &MainWindow::onEbsToggled);
    QFrame* ebsLine = new QFrame(settingsPanel);
    ebsLine->setGeometry(20, 120, 360, 2);
    ebsLine->setFrameShape(QFrame::HLine);
    ebsLine->setFrameShadow(QFrame::Sunken);

    // BSD Control
    bsdLabel = new QLabel("Blind Spots", settingsPanel);
    bsdLabel->setGeometry(20, 130, 200, 40);
    bsdLabel->setStyleSheet("font-size: 18px; color: #2c3e50;");
    bsdSwitch = new QCheckBox(settingsPanel);
    bsdSwitch->setGeometry(200, 130, 100, 30);
    bsdSwitch->setStyleSheet(R"( QCheckBox::indicator {width: 100px;height: 50px;}
                                 QCheckBox::indicator:unchecked {image: url(:/image/off-button.png);}
                                 QCheckBox::indicator:checked {image: url(:/image/switch-on.png);})");
    bsdSwitch->setChecked(true);
    connect(bsdSwitch, &QCheckBox::toggled, this, &MainWindow::onBsdToggled);
    QFrame* bsdLine = new QFrame(settingsPanel);
    bsdLine->setGeometry(20, 170, 360, 2);
    bsdLine->setFrameShape(QFrame::HLine);
    bsdLine->setFrameShadow(QFrame::Sunken);

    // TSR Control
    tsrLabel = new QLabel("Traffic Signs", settingsPanel);
    tsrLabel->setGeometry(20, 180, 200, 40);
    tsrLabel->setStyleSheet("font-size: 18px; color: #2c3e50;");
    tsrSwitch = new QCheckBox(settingsPanel);
    tsrSwitch->setGeometry(200, 180, 100, 30);
    tsrSwitch->setStyleSheet(R"( QCheckBox::indicator {width: 100px;height: 50px;}
                                 QCheckBox::indicator:unchecked {image: url(:/image/off-button.png);}
                                 QCheckBox::indicator:checked {image: url(:/image/switch-on.png);})");
    tsrSwitch->setChecked(true);
    connect(tsrSwitch, &QCheckBox::toggled, this, &MainWindow::onTsrToggled);
    QFrame* tsrLine = new QFrame(settingsPanel);
    tsrLine->setGeometry(20, 220, 360, 2);
    tsrLine->setFrameShape(QFrame::HLine);
    tsrLine->setFrameShadow(QFrame::Sunken);

    // allow resizing dynamically
    connect(this, &MainWindow::resized, this, [=](){
        sidePanel->setGeometry(0, 0, 100, this->height());
        settingsPanel->setGeometry(100,0,400,this->height());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);  // call base class

    int centerX = width() / 2;
    int labelWidth = 500;
    int labelHeight = 80;
    int windowWidth = this->width();
    int xOffset = 100; // Space for the side panel

    // Center all labels horizontally
    brakingStatusLabel->setGeometry(centerX - labelWidth/2, 30, labelWidth, labelHeight);
    leftBlindSpotLabel->setGeometry(centerX - labelWidth/2, 140, labelWidth, labelHeight);
    rightBlindSpotLabel->setGeometry(centerX - labelWidth/2, 250, labelWidth, labelHeight);
    trafficSignLabel->setGeometry(centerX - labelWidth/2, 360, 400, labelHeight);
    trafficSign->setGeometry(centerX - labelWidth/2 + 400 +10, 360, 80, 80);
    emit resized();

}

void MainWindow::updateBrakingStatus(const QString& status) {
    if (status == "SAFE") {
        brakingStatusLabel->hide();
    } else if (status == "WARNING") {
        brakingStatusLabel->setText("⚠️ SLOW DOWN !!!!");
        brakingStatusLabel->setStyleSheet("font-size: 24px; color: black; background-color: orange;");
        brakingStatusLabel->show();
    } else if (status == "DANGER") {
        brakingStatusLabel->setText("🚨 BRAKE !!!!!!");
        brakingStatusLabel->setStyleSheet("font-size: 24px; color: white; background-color: red;");
        brakingStatusLabel->show();
    }
}

void MainWindow::updateRightBlindSpotStatus(const QString& status){
    if (status == "SAFE") {
        rightBlindSpotLabel->hide();
    } else if (status == "WARNING") {
        rightBlindSpotLabel->setText("⚠️ Right Blind Spot: Vehicle Detected");
        rightBlindSpotLabel->setStyleSheet("font-size: 24px; color: black; background-color: orange;");
        rightBlindSpotLabel->show();
    } else if (status == "DANGER") {
        rightBlindSpotLabel->setText("🚨 Right Blind Spot: Immediate Hazard!");
        rightBlindSpotLabel->setStyleSheet("font-size: 24px; color: white; background-color: red;");
        rightBlindSpotLabel->show();
    }
}

void MainWindow::updateLeftBlindSpotStatus(const QString& status){
    if (status == "SAFE") {
        leftBlindSpotLabel->hide();
    } else if (status == "WARNING") {
        leftBlindSpotLabel->setText("⚠️ Left Blind Spot: Vehicle Detected");
        leftBlindSpotLabel->setStyleSheet("font-size: 24px; color: black; background-color: orange;");
        leftBlindSpotLabel->show();
    } else if (status == "DANGER") {
        leftBlindSpotLabel->setText("🚨 Left Blind Spot: Immediate Hazard!");
        leftBlindSpotLabel->setStyleSheet("font-size: 24px; color: white; background-color: red;");
        leftBlindSpotLabel->show();
    }
}

void MainWindow::displayTrafficSign(const QString& sign){
    QMap<QString, QString> signStyles = {
        {"Stop", "font-size: 24px; color: white; background-color: red;"},
        {"Red Light", "font-size: 24px; color: white; background-color: red;"},
        {"Green Light", "font-size: 24px; color: black; background-color: green;"}
        // default style for the rest
    };

    QString style = signStyles.value(sign, "font-size: 24px; color: black; background-color: white;");
    trafficSignLabel->setStyleSheet(style);
    trafficSignLabel->setText(sign);
    QPixmap pix(":signs/"+ sign + ".png");
    trafficSign->setPixmap(pix.scaled(80,80,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    trafficSign->show();
    trafficSignLabel->show();
    // Hide after 5 seconds (5000 ms)
    tsrTimer->start(5000);

}

void MainWindow::onSettingsButtonClicked() {
    spdlog::info("settings button clicked");
    toggleSittingsPanel();
}

void MainWindow::toggleSittingsPanel(){
    if (isSettingsPanelOpen) {
            settingsPanel->hide();
            isSettingsPanelOpen = false;
            spdlog::info("settings panel closed");
     } else {
            settingsPanel->show();
            isSettingsPanelOpen = true;
            spdlog::info("settings panel opened");
     }
}

void MainWindow::onEbsToggled(bool checked) {
    ebsSwitch->setText(checked ? "EBS: ON" : "EBS: OFF");
    spdlog::info("EBS toggled: {}", checked ? "ON" : "OFF");
    communication->publishToTopic("control/ebs", checked? "ON" : "OFF");
    if(!checked)
        brakingStatusLabel->hide();
}

void MainWindow::onBsdToggled(bool checked) {
    bsdSwitch->setText(checked ? "BSD: ON" : "BSD: OFF");
    spdlog::info("BSD toggled: {}", checked ? "ON" : "OFF");
    communication->publishToTopic("control/bsd", checked? "ON" : "OFF");
    if(!checked){
        rightBlindSpotLabel->hide();
        leftBlindSpotLabel->hide();
    }
}

void MainWindow::onTsrToggled(bool checked) {
    tsrSwitch->setText(checked ? "TSR: ON" : "TSR: OFF");
    spdlog::info("TSR toggled: {}", checked ? "ON" : "OFF");
    communication->publishToTopic("control/tsr", checked? "ON" : "OFF");
    if(!checked){
        trafficSign->hide();
        trafficSignLabel->hide();
    }
}

