//
// Created by mohsen on 1/7/17.
//

#ifndef DSPLAYER_SEEKBAR_H
#define DSPLAYER_SEEKBAR_H

#include <gtkmm.h>

namespace UI {
    class SeekBar : public Gtk::Container {
    public:
        SeekBar();

        ~SeekBar();

        typedef sigc::signal<void, double> OnChangedEventSignalType;

        OnChangedEventSignalType signal_changed();

        void requestLabel(const Glib::ustring &label);

        void requestRemoveLabel();

        void set_fraction(double value);
    protected:
        OnChangedEventSignalType onChangedEventSignal;

        virtual void on_size_request(Gtk::Requisition *requisition);

        virtual void on_size_allocate(Gtk::Allocation &allocation);

        virtual void forall_vfunc(gboolean include_internals, GtkCallback callback, gpointer callback_data);

        virtual void on_add(Gtk::Widget *child);

        virtual void on_remove(Gtk::Widget *child);

        virtual GType child_type_vfunc() const;

    private:

        Gtk::ProgressBar *progressbar;
        Gtk::Label *label;
        Gtk::EventBox *box;

        bool keyDown = false;

        bool onKeyDown(GdkEventButton *event);

        bool onKeyUp(GdkEventButton *event);

        bool onMouseMove(GdkEventMotion *event);

        void update(double x, double y);
    };
}


#endif //DSPLAYER_SEEKBAR_H
