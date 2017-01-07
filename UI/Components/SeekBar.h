//
// Created by mohsen on 1/7/17.
//

#ifndef DSPLAYER_SEEKBAR_H
#define DSPLAYER_SEEKBAR_H

#include <gtkmm/progressbar.h>

namespace UI {
    class SeekBar : public Gtk::ProgressBar {
    public:
        SeekBar();

        typedef sigc::signal<void, double> OnChangedEventSignalType;

        OnChangedEventSignalType signal_changed();

    protected:
        OnChangedEventSignalType onChangedEventSignal;
    private:
        bool keyDown = false;

        bool onKeyDown(GdkEventButton *event);

        bool onKeyUp(GdkEventButton *event);

        bool onMouseMove(GdkEventMotion *event);

        void update(double x, double y);
    };
}


#endif //DSPLAYER_SEEKBAR_H
