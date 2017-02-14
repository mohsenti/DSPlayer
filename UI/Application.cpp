//
// Created by mohsen on 1/3/17.
//

#include "Application.h"

UI::Application::Application(int argc, char **argv) : argc(argc), argv(argv) {
    application = new QApplication(argc, argv);
}

UI::Application::~Application() {
    delete mainWindow;
    delete application;
}

int UI::Application::run() {
    string appDir = Core::getHomeDirectory() + ".DSPlayer/";
    Core::createDirectory(appDir);
    InstanceCommunicate communicate(appDir + "SingleInstancePipeCommunicate.DSPlayer");
    if (communicate.serverIsRunning()) {
        communicate.start();
        for (int i = 1; i < argc; ++i) {
            communicate.writeMessage(1, argv[i]);
        }
        return 0;
    } else {
        communicate.start();
        mainWindow = new PlayerWindow(communicate);
        mainWindow->show();
        for (int i = 1; i < argc; ++i) {
            mainWindow->otherInstanceRequestAddFile(argv[i]);
        }
        int res = application->exec();
        communicate.stop();
        return res;
    }
}