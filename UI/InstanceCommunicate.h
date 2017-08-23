//
// Created by mohsen on 1/23/17.
//

#ifndef DSPLAYER_INSTANCECOMMUNICATEMESSAGE_H
#define DSPLAYER_INSTANCECOMMUNICATEMESSAGE_H

#include <fstream>
#include "Core/Core.h"

using namespace std;

typedef struct InstanceCommunicateMessage {
    int action;
    string message;
} InstanceCommunicateMessage;

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

    void writeMessage(int action, const string &message);

    InstanceCommunicateMessage readMessage();
};


#endif //DSPLAYER_INSTANCECOMMUNICATEMESSAGE_H
