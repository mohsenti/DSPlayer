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

    protected:
    private:
        bool keyDown = false;

        bool onKeyDown(GdkEventButton *event);

        bool onKeyUp(GdkEventButton *event);

        bool onMouseMove(GdkEventMotion *event);
    };
}


#endif //DSPLAYER_SEEKBAR_H
