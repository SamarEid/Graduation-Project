#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Communication/Communication.h"
#include "ADAS/ADAS_Notification.h"
#include "QPushButton"
#include "QCheckBox"
#include "QTimer"

#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Communication* comm,QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void updateBrakingStatus(const QString& status);
    void updateRightBlindSpotStatus(const QString& status);
    void updateLeftBlindSpotStatus(const QString& status);
    void displayTrafficSign(const QString& sign);
    void onSettingsButtonClicked();
    void toggleSittingsPanel();
    void onEbsToggled(bool checked);
    void onBsdToggled(bool checked);
    void onTsrToggled(bool checked);
signals:
    void resized();

protected:
    void resizeEvent(QResizeEvent* event) override;
private:
    Ui::MainWindow *ui;
    QWidget* sidePanel;
    QWidget* settingsPanel;
    bool isSettingsPanelOpen = false;
    QPushButton* settingsButton;
    Communication* communication;
    ADASNotification* notification;
    QLabel* brakingStatusLabel;
    QLabel* rightBlindSpotLabel;
    QLabel* leftBlindSpotLabel;
    QLabel* trafficSignLabel;
    QLabel* trafficSign;
    QTimer *tsrTimer;
    QLabel* adasControlLabel;
    QLabel* ebsLabel;
    QLabel* bsdLabel;
    QLabel* tsrLabel;

    QCheckBox* ebsSwitch;
    QCheckBox* bsdSwitch;
    QCheckBox* tsrSwitch;


};
#endif // MAINWINDOW_H
