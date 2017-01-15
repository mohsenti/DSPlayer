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
#include <QtGui/QTreeWidget>
#include <QtGui/QMenu>
#include <QFileInfo>

namespace UI {

    class PlayerWindow : public QWidget {
    Q_OBJECT

    private:
        QPushButton *btnPlay, *btnStop, *btnNext, *btnPrev;
        QSlider *hsVolume;
        SeekBar *pbSeek;
        QHBoxLayout *hbTopContainer;
        QVBoxLayout *vbMainContainer;

        QTreeWidget *twTracks;

        QTreeWidgetItem *createListItem(const QString &title, const QString &duration, const QString &album);

        void appendDirectory(const QFileInfo &fileInfo, QStringList &paths);

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

        void onHsVolumeValueChanged(int value);

        void twTracksShowContextMenu(const QPoint &point);

    public:

        explicit PlayerWindow(QWidget *parent = 0);

        virtual ~PlayerWindow();

    };

}

#endif //DSPLAYER_PLAYERWINDOW_H
