//
// Created by mohsen on 1/3/17.
//

#ifndef DSPLAYER_PLAYERWINDOW_H
#define DSPLAYER_PLAYERWINDOW_H

#include <QtWidgets>
#include <QtMultimedia/QtMultimedia>
#include "Core/Core.h"
#include <UI/Components/SeekBar.h>
#include <UI/Components/AudioTreeWidgetItem.h>
#include <UI/Components/TreeView.h>

namespace UI {

    class PlayerWindow : public QWidget {
    Q_OBJECT

    private:
        QPushButton *btnPlay, *btnStop, *btnNext, *btnPrev, *btnShuffle, *btnRepeat;
        QSlider *hsVolume;
        SeekBar *pbSeek;
        TreeView *tvTracks;
        QHBoxLayout *hbTopContainer;
        QVBoxLayout *vbMainContainer;

        QMediaPlayer *player;
        QMediaPlaylist *playlist;

        QSystemTrayIcon *trayIcon;
        QMenu *trayIconMenu;

        QTimer *instanceRequestTimer;
        bool instanceRequestInTime = false;

        void appendDirectory(const QDir &dir, QStringList &paths);

        void openFiles(const QStringList &paths);

        void savePlaylist(const QString &fileName);

        void restorePlaylist(const QString &fileName);

        void saveApplicationState(const QString &fileName);

        void restoreApplicationState(const QString &fileName);

        void updateAudioItemIcon(AudioTreeWidgetItem *item, QMediaPlayer::State newState);

        void prepareTrayIconContextMenu();

    protected:
        virtual void dragEnterEvent(QDragEnterEvent *event) override;

        virtual void dragMoveEvent(QDragMoveEvent *event) override;

        virtual void dragLeaveEvent(QDragLeaveEvent *event) override;

        virtual void dropEvent(QDropEvent *event) override;

    private slots:

        void onPlayTriggered();

        void onStopTriggered();

        void onNextTriggered();

        void onPrevTriggered();

        void onBtnRepeatToggled(bool checked);

        void onBtnShuffleToggled(bool checked);

        void onHsVolumeValueChanged(int value);

        void onTvTracksShowContextMenu(const QPoint &point);

        void onTvTracksItemActivated(QTreeWidgetItem *item, int column);

        void onTvItemsMoved(QList<int> from, QList<int> to);

        void onAddFileMenuTriggered(bool checked);

        void onAddFolderMenuTriggered(bool checked);

        void onQuitMenuTriggered(bool checked);

        void onRemoveMenuTriggered(bool checked);

        void onPbUserChangeValue(int value);

        void onPlaylistCurrentIndexChanged(int index);

        void onPlaylistMediaRemoved(int start, int end);

        void onPlayerPositionChanged(qint64 position);

        void onPlayerStateChanged(QMediaPlayer::State newState);

        void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

        void onInstanceRequestTimerTimeOut();

    public:

        explicit PlayerWindow(QWidget *parent = 0);

        virtual ~PlayerWindow();

        void otherInstanceRequestAddFile(string fileName);

    };

}

#endif //DSPLAYER_PLAYERWINDOW_H
