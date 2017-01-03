//
// Created by mohsen on 1/3/17.
//

#ifndef DSPLAYER_BASEWINDOW_H
#define DSPLAYER_BASEWINDOW_H

#include <gtkmm/window.h>

namespace UI {

    class BaseWindow : Gtk::Window {
    public:
        void add(Gtk::Widget *widget) { Gtk::Window::add(*widget); }
    };

}
#endif //DSPLAYER_BASEWINDOW_H
