//
// Created by mohsen on 1/4/17.
//

#include <iostream>
#include "gtkmm.h"

class CustomLoop : public Gtk::Main {
private:
    bool isQuit = false;
protected:
    void run_impl() override {
        while (!isQuit) {
            while (this->events_pending()) {
                this->iteration(false);
                std::cout << "Pending event iterated";
            }
        }
    }

    void quit_impl() override {
        isQuit = true;
        Gtk::Main::quit_impl();
    }

public:
    CustomLoop(int argc, char **argv) : Gtk::Main(argc, argv) {}
};

int main(int argc, char **argv) {
    CustomLoop customLoop(argc, argv);

    Gtk::Window aw;
    aw.set_size_request(400, 100);
    aw.set_position(Gtk::WindowPosition::WIN_POS_CENTER);
    customLoop.run(aw);
    return 0;
}