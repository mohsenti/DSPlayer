//
// Created by mohsen on 1/3/17.
//

#include "Application.h"

UI::Application::Application(int argc, char **argv) : argc(argc), argv(argv) {
    application = Gtk::Application::create(argc, argv, "ir.digiways.DSPlayer");
    mainWindow = new PlayerWindow();
}

UI::Application::~Application() {
    delete mainWindow;
}

int UI::Application::run() {
    return application->run(*mainWindow);
}
