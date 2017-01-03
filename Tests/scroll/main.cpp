//
// Created by mohsen on 1/3/17.
//
#include "gtkmm.h"

int main(int argc, char **argv) {
    Gtk::Main g_main(argc, argv);
    Gtk::Window aw;
    Gtk::HScale as(0, 101, 1);
    aw.add(as);
    as.show();
    aw.set_size_request(400, 100);
    aw.set_position(Gtk::WindowPosition::WIN_POS_CENTER);
    g_main.run(aw);
    return 0;
}