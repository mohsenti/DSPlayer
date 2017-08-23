#include <iostream>
#include "UI/Application.h"

int main(int argc, char **argv) {
    UI::Application application(argc, argv);
    return application.run();
}