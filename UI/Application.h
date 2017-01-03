//
// Created by mohsen on 1/3/17.
//

#ifndef DSPLAYER_APPLICATION_H
#define DSPLAYER_APPLICATION_H


#include <gtkmm.h>
#include "PlayerWindow.h"
#include "../Core/CoreTools.h"

namespace UI {

    class Application {
    private:
        Gtk::Main *application;
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
