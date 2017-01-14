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
    mainWindow = new PlayerWindow();
    mainWindow->show();
    return application->exec();
}
