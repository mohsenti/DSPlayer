//
// Created by mohsen on 1/22/17.
//

#ifndef DSPLAYER_UNIXDOMAINSOCKET_H
#define DSPLAYER_UNIXDOMAINSOCKET_H

#include <string>

namespace Core {

    class UnixDomainSocket {
    private:
        std::string key;
        int socketFd;

        int errorNumber;

    protected:
        UnixDomainSocket(int newSocket);

    public:

        UnixDomainSocket(std::string &key);

        bool hasError();

        bool bind();

        bool connect();

        bool listen();

        void unlink();

        UnixDomainSocket *accept();

        ssize_t read(char *buf, size_t size);

        ssize_t write(const char *buf, size_t size);

        virtual ~UnixDomainSocket();
    };

}

#endif //DSPLAYER_UNIXDOMAINSOCKET_H
