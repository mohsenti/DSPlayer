//
// Created by mohsen on 1/3/17.
//

#ifndef DSPLAYER_PLAYERWINDOW_H
#define DSPLAYER_PLAYERWINDOW_H

#include <QtWidgets>
#include <QtMultimedia/QtMultimedia>
#include "Core/Core.h"
#include <UI/Components/SeekBar.h>

namespace UI {

    class PlayerWindow : public QWidget {
    Q_OBJECT

    private:
        QPushButton *btnPlay, *btnStop, *btnNext, *btnPrev, *btnShuffle, *btnRepeat;
        QSlider *hsVolume;
        SeekBar *pbSeek;
        QTreeWidget *twTracks;
        QHBoxLayout *hbTopContainer;
        QVBoxLayout *vbMainContainer;

        QMediaPlayer *player;
        QMediaPlaylist *playlist;

        void appendDirectory(const QDir &dir, QStringList &paths);

        void openFiles(const QStringList &paths);

    protected:
        virtual void dragEnterEvent(QDragEnterEvent *event) override;

        virtual void dragMoveEvent(QDragMoveEvent *event) override;

        virtual void dragLeaveEvent(QDragLeaveEvent *event) override;

        virtual void dropEvent(QDropEvent *event) override;

    private slots:

        void onBtnPlayClicked();

        void onBtnStopClicked();

        void onBtnNextClicked();

        void onBtnPrevClicked();

        void onBtnRepeatToggled(bool checked);

        void onBtnShuffleToggled(bool checked);

        void onHsVolumeValueChanged(int value);

        void twTracksShowContextMenu(const QPoint &point);

        void onAddFileMenuTriggered(bool checked);

        void onAddFolderMenuTriggered(bool checked);

        void onQuitMenuTriggered(bool checked);

        void onRemoveMenuTriggered(bool checked);

        void onPbUserChangeValue(int value);

    public:

        explicit PlayerWindow(QWidget *parent = 0);

        virtual ~PlayerWindow();

    };

}

#endif //DSPLAYER_PLAYERWINDOW_H
