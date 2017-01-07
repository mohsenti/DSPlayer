//
// Created by mohsen on 1/3/17.
//

#ifndef DSPLAYER_PLAYERWINDOW_H
#define DSPLAYER_PLAYERWINDOW_H

#include <gtkmm.h>
#include "Components/SeekBar.h"

namespace UI {

    class PlayerWindow : public Gtk::Window {
    private:
        Gtk::Button *btnPlay, *btnStop, *btnNext, *btnPrev;
        Gtk::HScale *hsVolume;
        SeekBar *pbSeek;
        Gtk::HBox *hbTopContainer;
        Gtk::VBox *vbMainContainer, *vbProgressContainer;

        void onBtnPlayClicked();

        void onBtnStopClicked();

        void onBtnNextClicked();

        void onBtnPrevClicked();

        void onHsVolumeValueChanged();

        void onPbSeekChanged(double value);

    public:

        PlayerWindow();

        virtual ~PlayerWindow();

    };

}

#endif //DSPLAYER_PLAYERWINDOW_H
