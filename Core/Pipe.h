//
// Created by mohsen on 1/23/17.
//

#ifndef DSPLAYER_PIPE_H
#define DSPLAYER_PIPE_H

#include <string>
#include <stddef.h>

namespace Core {
    class Pipe {
    private:
        std::string key;
        int fd;
        int errorNumber;

        void setError();

    protected:
    public:
        Pipe(const std::string &key);

        bool hasError();

        void resetError();

        bool exists();

        bool create();

        bool openRead();

        bool openWrite();

        void lock();

        bool nonBlockingLock();

        void unlock();

        ssize_t read(char *buf, size_t count);

        ssize_t write(const char *buf, size_t count);

        void close();

        bool unlink();

    };
}

#endif //DSPLAYER_PIPE_H
