#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "Communication/Communication.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class startWindow; }
QT_END_NAMESPACE

class startWindow : public QWidget
{
    Q_OBJECT

public:
    explicit startWindow(Communication* comm,QWidget *parent = nullptr);
    ~startWindow();
private slots:
    void on_startButton_clicked();

private:
    Ui::startWindow *ui;
    Communication* communication;
};

#endif // STARTWINDOW_H
