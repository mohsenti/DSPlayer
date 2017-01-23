//
// Created by mohsen on 1/3/17.
//

#ifndef DSPLAYER_APPLICATION_H
#define DSPLAYER_APPLICATION_H

#include <QGuiApplication>

#include "PlayerWindow.h"
#include "../Core/Core.h"

namespace UI {

    class Application {
    private:
        QApplication *application;
        PlayerWindow *mainWindow;

        int argc;
        char **argv;
    public:
        Application(int argc, char **argv);

        virtual ~Application();

        int run();
    };

}

#endif //DSPLAYER_APPLICATION_H
