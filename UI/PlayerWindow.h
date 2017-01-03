//
// Created by mohsen on 1/3/17.
//

#ifndef DSPLAYER_PLAYERWINDOW_H
#define DSPLAYER_PLAYERWINDOW_H

#include <gtkmm.h>

namespace UI {

    class PlayerWindow : public Gtk::Window {
    private:
    protected:
        Gtk::Button *btnPlay, *btnStop, *btnNext, *btnPrev;
        Gtk::VolumeButton *btnVolume;
//        Gtk::SeekBar

        void onBtnPlayClicked();

        void onBtnStopClicked();

        void onBtnNextClicked();

        void onBtnPrevClicked();

        void onVolBtnValueChanged();

    public:

        PlayerWindow();

        virtual ~PlayerWindow();

    };

}

#endif //DSPLAYER_PLAYERWINDOW_H
