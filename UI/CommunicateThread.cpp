//
// Created by mohsen on 2/13/17.
//

#include "CommunicateThread.h"

void CommunicateThread::run() {
    qDebug("Hello World!");
    while (true) {
        InstanceCommunicateMessage message = this->communicate.readMessage();
        emit messageReceived(message);
    }
}

CommunicateThread::CommunicateThread(InstanceCommunicate &communicate) : communicate(communicate) {
    qRegisterMetaType<InstanceCommunicateMessage>("InstanceCommunicateMessage");
}