//
// Created by mohsen on 1/3/17.
//

#ifndef DSPLAYER_PLAYERWINDOW_H
#define DSPLAYER_PLAYERWINDOW_H

#include <gtkmm.h>
#include "Components/BaseWindow.h"

namespace UI {

    class PlayerWindow : public BaseWindow {
    private:
    protected:
        Gtk::Button *btnPlay, *btnStop, *btnNext, *btnPrev;
        Gtk::HScale *hsVolume;
        Gtk::ProgressBar *pbSeek;
        Gtk::HBox *hbTopContainer;
        Gtk::VBox *vbMainContainer, *vbProgressContainer;

        void onBtnPlayClicked();

        void onBtnStopClicked();

        void onBtnNextClicked();

        void onBtnPrevClicked();

        void onHsVolumeValueChanged();

    public:

        PlayerWindow();

        virtual ~PlayerWindow();

    };

}

#endif //DSPLAYER_PLAYERWINDOW_H
