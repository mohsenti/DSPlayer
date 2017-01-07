//
// Created by mohsen on 1/7/17.
//

#include <iostream>
#include "SeekBar.h"

UI::SeekBar::SeekBar() : Gtk::Container() {
    //Create controls
    progressbar = new Gtk::ProgressBar();
    label = new Gtk::Label();
    box = new Gtk::EventBox();
    box->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("green")); // Label modify_bg not work !!!!!!!!!!!

    box->set_parent(*this);
    box->add(*label);

    box->set_visible(false);

    progressbar->set_parent(*this);

    set_has_window(false);
    set_redraw_on_allocate(false);
    progressbar->add_events(Gdk::EventMask::BUTTON_PRESS_MASK);
    progressbar->add_events(Gdk::EventMask::BUTTON_RELEASE_MASK);
    progressbar->add_events(Gdk::EventMask::POINTER_MOTION_MASK);
    progressbar->signal_button_press_event().connect(sigc::mem_fun(*this, &SeekBar::onKeyDown));
    progressbar->signal_button_release_event().connect(sigc::mem_fun(*this, &SeekBar::onKeyUp));
    progressbar->signal_motion_notify_event().connect(sigc::mem_fun(*this, &SeekBar::onMouseMove));

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

bool UI::SeekBar::onTimeoutLabel() {
    this->requestRemoveLabel();
    return false;
}

void UI::SeekBar::update(double x, double y) {
    double percent = x / progressbar->get_width();
    if (percent > 1)
        percent = 1;
    if (percent < 0)
        percent = 0;
    onChangedEventSignal.emit(percent);
}

UI::SeekBar::OnChangedEventSignalType UI::SeekBar::signal_changed() {
    return onChangedEventSignal;
}

void UI::SeekBar::requestLabel(const Glib::ustring &label) {
    this->label->set_label(label);
    this->box->set_visible(true);

    if (timeOutConnection.connected())
        timeOutConnection.disconnect();
    timeOutConnection = Glib::signal_timeout().connect(sigc::mem_fun(*this, &SeekBar::onTimeoutLabel), 1000);

}

void UI::SeekBar::requestRemoveLabel() {
    this->box->set_visible(false);
}

void UI::SeekBar::set_fraction(double value) {
    progressbar->set_fraction(value);
}

void UI::SeekBar::on_size_request(Gtk::Requisition *requisition) {
    *requisition = Gtk::Requisition();
    Gtk::Requisition labelReq = label->size_request();
    Gtk::Requisition progressReq = progressbar->size_request();
    requisition->height = labelReq.height;
    requisition->width = progressReq.width;
}

void UI::SeekBar::on_size_allocate(Gtk::Allocation &allocation) {
    set_allocation(allocation);
    Gtk::Allocation labelAlloc, progressbarAlloc;

    int labelWidth, labelHeight;
    label->get_layout()->get_pixel_size(labelWidth, labelHeight);

    labelAlloc.set_x(allocation.get_x() + (allocation.get_width() - labelWidth) / 2);
    labelAlloc.set_y(allocation.get_y());
    labelAlloc.set_width(labelWidth);
    labelAlloc.set_height(allocation.get_height());

    box->size_allocate(labelAlloc);

    progressbarAlloc.set_x(allocation.get_x());
    progressbarAlloc.set_y(allocation.get_y() + (allocation.get_height() / 3));
    progressbarAlloc.set_width(allocation.get_width());
    progressbarAlloc.set_height(allocation.get_height() / 3);

    progressbar->size_allocate(progressbarAlloc);
}

void UI::SeekBar::forall_vfunc(gboolean include_internals, GtkCallback callback, gpointer callback_data) {
    callback((GtkWidget *) progressbar->gobj(), callback_data);
    callback((GtkWidget *) box->gobj(), callback_data);
}

void UI::SeekBar::on_add(Gtk::Widget *child) {}

void UI::SeekBar::on_remove(Gtk::Widget *child) {}

GType UI::SeekBar::child_type_vfunc() const {
    return Gtk::Widget::get_type();
}

UI::SeekBar::~SeekBar() {
    delete box;
    delete progressbar;
    delete label;
}
