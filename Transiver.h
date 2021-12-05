//
// Created by UlrikKarlsson on 2021-10-27.
//

#ifndef TEST_TRANSIVER_H
#define TEST_TRANSIVER_H


class Transiver {
private:
    unsigned long time {};

    int CE {};
    int CSN {};

public:
    Transiver(int CE, int CSN);
    ~Transiver();

    void setAddress();
    void setPALevel();
    void setAsTransmitter();
    void setAsReceiver();

    void send(int message);
    void send(bool state);

    bool receive(int timeout);
};


#endif //TEST_TRANSIVER_H
