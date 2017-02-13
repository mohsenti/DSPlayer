//
// Created by mohsen on 1/23/17.
//

#include "InstanceCommunicate.h"
#include <QtDebug>
#include <fcntl.h>
#include <sys/file.h>
#include <zconf.h>
#include <sys/stat.h>

#ifdef __linux__

void InstanceCommunicate::start() {
    if (serverIsRunning()) {
        fd = open(fileName.c_str(), O_WRONLY);
        flock(fd, LOCK_SH | LOCK_NB);
    } else {
        if (!Core::fileExists(fileName)) {
            if (mkfifo(fileName.c_str(), 438) != 0) {
                //Todo:throw exception here, failed to create pipe
            }
        }
        fd = open(fileName.c_str(), O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
        flock(fd, LOCK_SH | LOCK_NB);
    }
}

void InstanceCommunicate::stop() {
    close(fd);
}

bool InstanceCommunicate::serverIsRunning() {
    if (!Core::fileExists(fileName))
        return false;
    int fd = open(fileName.c_str(), O_WRONLY | O_NONBLOCK);
    if (fd == -1) {
        //delete orphaned pipe
        unlink(fileName.c_str());
        return false;
    } else {
        close(fd);
        return true;
    }
}

InstanceCommunicate::InstanceCommunicate(const string &fileName) {
    this->fileName = Core::getTmpDirectory() + fileName;
}

void InstanceCommunicate::writeMessage(int action, const string &message) {
    write(fd, &action, sizeof(int));
    int messageSize = (int) (message.length() * sizeof(char));
    write(fd, &messageSize, sizeof(int));
    if (messageSize > 0)
        write(fd, message.c_str(), messageSize);
}

InstanceCommunicateMessage InstanceCommunicate::readMessage() {
    InstanceCommunicateMessage result;
    read(fd, &result.action, sizeof(int));
    int messageSize = 0;
    read(fd, &messageSize, sizeof(int));
    if (messageSize > 0) {
        char *message = new char[messageSize + 1];
        read(fd, message, messageSize);
        message[messageSize] = 0;
        result.message = message;
        delete message;
    }
    return result;
}

#endif