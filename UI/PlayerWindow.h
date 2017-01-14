//
// Created by mohsen on 1/3/17.
//

#ifndef DSPLAYER_PLAYERWINDOW_H
#define DSPLAYER_PLAYERWINDOW_H

#include <qt4/QtGui/QPushButton>
#include <qt4/QtGui/QProgressBar>
#include <qt4/QtGui/QHBoxLayout>
#include <qt4/QtGui/QSlider>
#include <UI/Components/SeekBar.h>

namespace UI {

    class PlayerWindow : public QWidget {
    Q_OBJECT

    private:
        QPushButton *btnPlay, *btnStop, *btnNext, *btnPrev;
        QSlider *hsVolume;
        SeekBar *pbSeek;
        QHBoxLayout *hbTopContainer;
        QVBoxLayout *vbMainContainer;

    private slots:

        void onBtnPlayClicked();

        void onBtnStopClicked();

        void onBtnNextClicked();

        void onBtnPrevClicked();

        void onHsVolumeValueChanged(int value);

    public:

        explicit PlayerWindow(QWidget *parent = 0);

        virtual ~PlayerWindow();

    };

}

#endif //DSPLAYER_PLAYERWINDOW_H
