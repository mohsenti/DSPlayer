//
// Created by mohsen on 1/3/17.
//

#include "Application.h"

UI::Application::Application(int argc, char **argv) : argc(argc), argv(argv) {
    application = new Gtk::Main(argc, argv, false);
    mainWindow = new PlayerWindow();
}

UI::Application::~Application() {
    delete mainWindow;
    delete application;
}

int UI::Application::run() {
    application->run(*mainWindow);
    return 0;
}
