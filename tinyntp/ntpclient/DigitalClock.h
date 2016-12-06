//
// Created by streamer on 16-11-27.
//

#ifndef TINYRPC_DIGITALCLOCK_H
#define TINYRPC_DIGITALCLOCK_H

#include <QLCDNumber>
#include "client/client.h"

class DigitalClock : public QLCDNumber {
    Q_OBJECT

public:
    DigitalClock(std::string ip, int port, int verify_id, QWidget *parent = 0);

public slots:
    void showTime();

private:
    tinyrpc::client client;
    int verify_id;

};


#endif //TINYRPC_DIGITALCLOCK_H
