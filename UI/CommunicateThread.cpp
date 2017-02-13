//
// Created by mohsen on 1/23/17.
//

#include "CommunicateThread.h"
#include <QtDebug>
#include <fcntl.h>
#include <sys/file.h>
#include <zconf.h>
#include <sys/stat.h>

#ifdef __linux__

void CommunicateThread::run() {

}

void CommunicateThread::start() {
    if (serverIsRunning()) {
        fd = open(fileName.c_str(),O_WRONLY);
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

void CommunicateThread::stop() {
    close(fd);
}

bool CommunicateThread::serverIsRunning() {
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

#endif