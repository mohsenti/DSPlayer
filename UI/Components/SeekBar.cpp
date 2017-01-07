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
    if (event->button == 1) {
        keyDown = true;
        update(event->x, event->y);
    }
    return false;
}

bool UI::SeekBar::onKeyUp(GdkEventButton *event) {
    if (event->button == 1) {
        keyDown = false;
        update(event->x, event->y);
    }
    return false;
}

bool UI::SeekBar::onMouseMove(GdkEventMotion *event) {
    if (keyDown) {
        update(event->x, event->y);
    }
    return false;
}

void UI::SeekBar::update(double x, double y) {
    onChangedEventSignal.emit(x / this->get_width());
}

UI::SeekBar::OnChangedEventSignalType UI::SeekBar::signal_changed() {
    return onChangedEventSignal;
}
