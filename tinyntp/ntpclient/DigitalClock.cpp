//
// Created by streamer on 16-11-27.
//

#include <QtWidgets>
#include "DigitalClock.h"


DigitalClock::DigitalClock(std::string ip, int port, int verify_id, QWidget *parent)
        : QLCDNumber(parent),client(ip, port), verify_id(verify_id)
{
    setSegmentStyle(Filled);
    setDigitCount(8);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(200);

    showTime();

    setWindowTitle(tr("数字时钟"));
    resize(200, 100);
}


void DigitalClock::showTime()
{
    QTime time_base, current_time, flag;
    QString text = "88:88:88";
    flag.start();
    QString time = QString::fromStdString(this->client.call("gettime", this->verify_id).as<std::string>());
    int cost_time = flag.elapsed() / 2;

    if (!time.isNull()) {
        time_base = QTime::fromString(time, "hh:mm:ss");

        current_time = time_base.addMSecs(cost_time);
        text = current_time.toString("hh:mm:ss");
    }

    display(text);
}




