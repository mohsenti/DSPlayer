//
// Created by mohsen on 1/22/17.
//

#include "UnixDomainSocket.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <zconf.h>

Core::UnixDomainSocket::UnixDomainSocket(std::string &key) : key(key) {
    if ((this->socketFd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        this->errorNumber = errno;
        return;
    }
}

Core::UnixDomainSocket::UnixDomainSocket(int newSocket) : socketFd(newSocket) {

}

bool Core::UnixDomainSocket::hasError() {
    return this->errorNumber != 0;
}

bool Core::UnixDomainSocket::bind() {
    if (this->hasError())
        return false;
    struct sockaddr_un local;
    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, key.c_str());
    auto len = strlen(local.sun_path) + sizeof(local.sun_family);
    if (::bind(this->socketFd, (struct sockaddr *) &local, (socklen_t) len) == -1) {
        this->errorNumber = errno;
        return false;
    }
    return true;
}

bool Core::UnixDomainSocket::connect() {
    struct sockaddr_un remote;
    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, key.c_str());
    auto len = strlen(remote.sun_path) + sizeof(remote.sun_family);
    if (::connect(socketFd, (struct sockaddr *) &remote, (socklen_t) len) == -1) {
        this->errorNumber = errno;
        return false;
    }
    return true;
}

bool Core::UnixDomainSocket::listen() {
    if (this->hasError())
        return false;
    if (::listen(socketFd, 5) == -1) {
        this->errorNumber = errno;
        return false;
    }
    return true;
}

void Core::UnixDomainSocket::unlink() {
    ::unlink(key.c_str());
}

Core::UnixDomainSocket *Core::UnixDomainSocket::accept() {
    if (this->hasError())
        return nullptr;
    int newSocket;
    struct sockaddr remote;
    socklen_t t;
    if ((newSocket = ::accept(socketFd, (struct sockaddr *) &remote, &t)) == -1) {
        this->errorNumber = errno;
        return nullptr;
    }
    return new UnixDomainSocket(newSocket);
}

ssize_t Core::UnixDomainSocket::read(char *buf, size_t size) {
    if (this->hasError())
        return -1;
    return recv(socketFd, buf, size, 0);
}

ssize_t Core::UnixDomainSocket::write(const char *buf, size_t size) {
    if (this->hasError())
        return -1;
    return send(socketFd, buf, size, 0);
}

Core::UnixDomainSocket::~UnixDomainSocket() {
    close(socketFd);
}
