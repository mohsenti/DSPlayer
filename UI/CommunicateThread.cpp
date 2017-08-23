//
// Created by mohsen on 2/13/17.
//

#include "CommunicateThread.h"

void CommunicateThread::run() {
    while (!terminated) {
        QMutexLocker locker(&mutex);
        InstanceCommunicateMessage message = this->communicate.readMessage();
        if (message.action != 0)
                emit messageReceived(message);
        locker.unlock();
        msleep(10);
    }
}

void CommunicateThread::terminate() {
    QMutexLocker locker(&mutex);
    terminated = true;
}

CommunicateThread::CommunicateThread(InstanceCommunicate &communicate) : communicate(communicate) {
    qRegisterMetaType<InstanceCommunicateMessage>("InstanceCommunicateMessage");
}