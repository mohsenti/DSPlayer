//
// Created by mohsen on 2/13/17.
//

#ifndef DSPLAYER_COMMUNICATETHREAD_H
#define DSPLAYER_COMMUNICATETHREAD_H

#include <QtWidgets>
#include "InstanceCommunicate.h"

class CommunicateThread : public QThread {
Q_OBJECT
private:
    InstanceCommunicate &communicate;
    bool terminated = false;
    QMutex mutex;
public:
    CommunicateThread(InstanceCommunicate &communicate);

    void terminate();

protected:
    void run();

signals:

    void messageReceived(const InstanceCommunicateMessage &message);
};


#endif //DSPLAYER_COMMUNICATETHREAD_H
