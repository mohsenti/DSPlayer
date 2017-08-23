//
// Created by mohsen on 1/23/17.
//

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>
#include <zconf.h>
#include "Pipe.h"

Core::Pipe::Pipe(const std::string &key) : key(key), fd(0), errorNumber(0) {}

void Core::Pipe::setError() {
    this->errorNumber = errno;
}

bool Core::Pipe::hasError() {
    return this->errorNumber != 0;
}

void Core::Pipe::resetError() {
    this->errorNumber = 0;
}

bool Core::Pipe::exists() {
    struct stat buffer;
    return (stat(key.c_str(), &buffer) == 0);
}

bool Core::Pipe::create() {
    if (mkfifo(key.c_str(), 0666) == -1) {
        setError();
        return false;
    }
    return true;
}

bool Core::Pipe::openRead() {
    int fd = ::open(key.c_str(), O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        setError();
        return false;
    }
    this->fd = fd;
    return true;
}

bool Core::Pipe::openWrite() {
    int fd = ::open(key.c_str(), O_WRONLY | O_NONBLOCK);
    if (fd == -1) {
        setError();
        return false;
    }
    this->fd = fd;
    return true;
}

void Core::Pipe::lock() {
    flock(this->fd, LOCK_EX);
}

bool Core::Pipe::nonBlockingLock() {
    if (flock(this->fd, LOCK_EX | LOCK_NB) == -1) {
        setError();
        return false;
    }
    return true;
}

void Core::Pipe::unlock() {
    flock(this->fd, LOCK_UN);
}

ssize_t Core::Pipe::read(char *buf, size_t count) {
    return ::read(fd, buf, count);
}

ssize_t Core::Pipe::write(const char *buf, size_t count) {
    return ::write(fd, buf, count);
}

void Core::Pipe::close() {
    ::close(fd);
}

bool Core::Pipe::unlink() {
    if (::unlink(key.c_str()) == -1) {
        setError();
        return false;
    }
    return true;
}
