//
// Created by mohsen on 1/3/17.
//

#include "Application.h"

UI::Application::Application(int argc, char **argv) : argc(argc), argv(argv) {
    application = new QApplication(argc, argv);
    mainWindow = new PlayerWindow();
}

UI::Application::~Application() {
    delete mainWindow;
    delete application;
}

int UI::Application::run() {
    return application->exec();
}
