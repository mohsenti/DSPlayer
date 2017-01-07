//
// Created by mohsen on 1/7/17.
//

#include "SeekBar.h"

UI::SeekBar::SeekBar() : Gtk::ProgressBar() {
    add_events(Gdk::EventMask::BUTTON_PRESS_MASK);
    add_events(Gdk::EventMask::BUTTON_RELEASE_MASK);
    add_events(Gdk::EventMask::POINTER_MOTION_MASK);
    signal_button_press_event().connect(sigc::mem_fun(*this, &SeekBar::onKeyDown));
    signal_button_release_event().connect(sigc::mem_fun(*this, &SeekBar::onKeyUp));
    signal_motion_notify_event().connect(sigc::mem_fun(*this, &SeekBar::onMouseMove));
}

bool UI::SeekBar::onKeyDown(GdkEventButton *event) {
    return false;
}

bool UI::SeekBar::onKeyUp(GdkEventButton *event) {
    return false;
}

bool UI::SeekBar::onMouseMove(GdkEventMotion *event) {
    return false;
}
