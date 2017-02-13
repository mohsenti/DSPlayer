//
// Created by mohsen on 1/23/17.
//

#ifndef DSPLAYER_COMMUNICATETHREAD_H
#define DSPLAYER_COMMUNICATETHREAD_H

#include <QtCore/QThread>
#include <fstream>
#include "Core/Core.h"

using namespace std;

class CommunicateThread {
private:
    int fd;
    string fileName;
protected:
    virtual void run();

public:
    void start();

    bool serverIsRunning();

    void stop();
};


#endif //DSPLAYER_COMMUNICATETHREAD_H
