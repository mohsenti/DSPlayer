//
// Created by mohsen on 1/23/17.
//

#ifndef DSPLAYER_COMMUNICATETHREAD_H
#define DSPLAYER_COMMUNICATETHREAD_H

#include <QtCore/QThread>
#include <fstream>
#include "Core/Core.h"

using namespace std;

class InstanceCommunicate {
private:
    int fd;
    string fileName;
protected:

public:
    InstanceCommunicate(const string &fileName);

    void start();

    bool serverIsRunning();

    void stop();
};


#endif //DSPLAYER_COMMUNICATETHREAD_H
