//
// Created by mohsen on 1/3/17.
//

#include <UI/Components/AudioTreeWidgetItem.h>
#include "PlayerWindow.h"

void UI::PlayerWindow::onBtnPlayClicked() {
    if (playlist->mediaCount() == 0)
        return;
    if (player->state() == QMediaPlayer::PlayingState) {
        player->pause();
        btnPlay->setIcon(QIcon::fromTheme("media-playback-start"));
    } else {
        player->play();
        btnPlay->setIcon(QIcon::fromTheme("media-playback-pause"));
    }
}

void UI::PlayerWindow::onBtnStopClicked() {
    if (player->state() == QMediaPlayer::PlayingState || player->state() == QMediaPlayer::PausedState)
        player->stop();
}

void UI::PlayerWindow::onBtnNextClicked() {
    if (playlist->mediaCount() == 0)
        return;
    playlist->next();
}

void UI::PlayerWindow::onBtnPrevClicked() {
    if (playlist->mediaCount() == 0)
        return;
    playlist->previous();
}

void UI::PlayerWindow::onBtnRepeatToggled(bool checked) {

}

void UI::PlayerWindow::onBtnShuffleToggled(bool checked) {
    if (checked)
        playlist->setPlaybackMode(QMediaPlaylist::Random);
    else playlist->setPlaybackMode(QMediaPlaylist::Sequential);
}

void UI::PlayerWindow::onHsVolumeValueChanged(int value) {
    player->setVolume(value);
}

void UI::PlayerWindow::onPbUserChangeValue(int value) {
    if (player->isSeekable()) {
        player->setPosition(value);
        pbSeek->requestLabel(Core::formatSecondsToTime(value / 1000).c_str());
    }
}

void UI::PlayerWindow::onPlaylistCurrentIndexChanged(int index) {
    if (index == -1 && btnRepeat->isChecked()) {
        playlist->next();
        index = 0;
        player->play();
    }
    AudioTreeWidgetItem *audioItem = (AudioTreeWidgetItem *) twTracks->topLevelItem(index);
    if (audioItem != nullptr) {
        pbSeek->setValue(0);
        pbSeek->setRange(0, audioItem->getDuration());
    }
    twTracks->setCurrentItem(audioItem);
}

void UI::PlayerWindow::onPlayerPositionChanged(qint64 position) {
    pbSeek->setValue(position);
}

void UI::PlayerWindow::onPlaylistMediaRemoved(int start, int end) {
    for (int i = start; i <= end; i++)
        delete twTracks->takeTopLevelItem(i);
}

void UI::PlayerWindow::onAddFileMenuTriggered(bool checked) {
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::FileMode::ExistingFiles);
    fileDialog.exec();
    openFiles(fileDialog.selectedFiles());
}

void UI::PlayerWindow::onAddFolderMenuTriggered(bool checked) {
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::FileMode::DirectoryOnly);
    fileDialog.exec();
    QStringList folders = fileDialog.selectedFiles();
    QStringList files;
    for (auto it = folders.begin(); it != folders.end(); it++) {
        appendDirectory(QDir(*it), files);
    }
    openFiles(files);
}

void UI::PlayerWindow::onQuitMenuTriggered(bool checked) {
    QApplication::quit();
}

void UI::PlayerWindow::onRemoveMenuTriggered(bool checked) {
    auto list = twTracks->selectedItems();
    for (auto it = list.begin(); it != list.end(); it++) {
        delete *it;
    }
}

void UI::PlayerWindow::twTracksShowContextMenu(const QPoint &point) {
    QPoint globalPoint = twTracks->mapToGlobal(point);
    QMenu twMenu;
    if (twTracks->selectedItems().size() > 0) {
        QAction *item = twMenu.addAction("Remove");
        connect(item, SIGNAL(triggered(bool)), this, SLOT(onRemoveMenuTriggered(bool)));

        twMenu.addSeparator();
    }
    QAction *item = twMenu.addAction("Add File");
    connect(item, SIGNAL(triggered(bool)), this, SLOT(onAddFileMenuTriggered(bool)));

    item = twMenu.addAction("Add Folder");
    connect(item, SIGNAL(triggered(bool)), this, SLOT(onAddFolderMenuTriggered(bool)));

    twMenu.addSeparator();
    item = twMenu.addAction("Quit");

    connect(item, SIGNAL(triggered(bool)), this, SLOT(onQuitMenuTriggered(bool)));
    twMenu.exec(globalPoint);
}

UI::PlayerWindow::PlayerWindow(QWidget *parent) : QWidget(parent) {
    //Create controls

    vbMainContainer = new QVBoxLayout();
    hbTopContainer = new QHBoxLayout();

    btnPlay = new QPushButton(QIcon::fromTheme("media-playback-start"), "", this);
    btnStop = new QPushButton(QIcon::fromTheme("media-playback-stop"), "", this);
    btnPrev = new QPushButton(QIcon::fromTheme("media-skip-backward"), "", this);
    btnNext = new QPushButton(QIcon::fromTheme("media-skip-forward"), "", this);
    btnRepeat = new QPushButton(QIcon::fromTheme("media-playlist-repeat"), "", this);
    btnShuffle = new QPushButton(QIcon::fromTheme("media-playlist-shuffle"), "", this);
    hsVolume = new QSlider(Qt::Horizontal, this);
    pbSeek = new SeekBar(this);

    twTracks = new QTreeWidget(this);

    //Init controls

    btnShuffle->setCheckable(true);
    btnRepeat->setCheckable(true);

    hsVolume->setFixedWidth(100);
    hsVolume->setRange(0, 100);
    //Todo: restore volume from previous session
    hsVolume->setValue(50);

    pbSeek->setMinimumWidth(250);
    pbSeek->setRange(0, 100);
    pbSeek->setValue(0);

    twTracks->setColumnCount(3);
    QStringList labels;
    labels << "Track" << "Duration" << "Album";
    twTracks->setHeaderLabels(labels);
    twTracks->setContextMenuPolicy(Qt::CustomContextMenu);
    twTracks->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);

    //Init signals

    connect(btnPlay, SIGNAL(clicked()), this, SLOT(onBtnPlayClicked()));
    connect(btnNext, SIGNAL(clicked()), this, SLOT(onBtnNextClicked()));
    connect(btnPrev, SIGNAL(clicked()), this, SLOT(onBtnPrevClicked()));
    connect(btnStop, SIGNAL(clicked()), this, SLOT(onBtnStopClicked()));
    connect(btnRepeat, SIGNAL(toggled(bool)), this, SLOT(onBtnRepeatToggled(bool)));
    connect(btnShuffle, SIGNAL(toggled(bool)), this, SLOT(onBtnShuffleToggled(bool)));
    connect(hsVolume, SIGNAL(valueChanged(int)), this, SLOT(onHsVolumeValueChanged(int)));
    connect(twTracks, SIGNAL(customContextMenuRequested(
                                     const QPoint&)), this, SLOT(twTracksShowContextMenu(
                                                                         const QPoint&)));
    connect(pbSeek, SIGNAL(userChangedValue(int)), this, SLOT(onPbUserChangeValue(int)));

    //Arrange controls

    vbMainContainer->setAlignment(Qt::AlignmentFlag::AlignTop);
    vbMainContainer->addLayout(hbTopContainer);

    hbTopContainer->addWidget(btnPlay);
    hbTopContainer->addWidget(btnStop);
    hbTopContainer->addWidget(btnPrev);
    hbTopContainer->addWidget(btnNext);
    hbTopContainer->addWidget(btnRepeat);
    hbTopContainer->addWidget(btnShuffle);
    hbTopContainer->addWidget(pbSeek);
    hbTopContainer->addWidget(hsVolume);

    vbMainContainer->addWidget(twTracks);

    setLayout(vbMainContainer);

    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(),
                                          QApplication::desktop()->availableGeometry()));
    this->setAcceptDrops(true);

    //Create and init player
    player = new QMediaPlayer;
    playlist = new QMediaPlaylist;

    player->setVolume(hsVolume->value());
    player->setPlaylist(playlist);

    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(onPlayerPositionChanged(qint64)));
    connect(playlist, SIGNAL(currentIndexChanged(int)), this, SLOT(onPlaylistCurrentIndexChanged(int)));
    connect(playlist, SIGNAL(mediaRemoved(int, int)), this, SLOT(onPlaylistMediaRemoved(int, int)));

    //Todo: restore last playlist
}

UI::PlayerWindow::~PlayerWindow() {

    //destroy controls

    delete hbTopContainer;
    delete vbMainContainer;
    delete btnPlay;
    delete btnNext;
    delete btnPrev;
    delete btnStop;
    delete hsVolume;
    delete pbSeek;
    delete twTracks;

    delete playlist;
    delete player;
}

void UI::PlayerWindow::dragEnterEvent(QDragEnterEvent *event) {
    event->acceptProposedAction();
    QWidget::dragEnterEvent(event);
}

void UI::PlayerWindow::dragMoveEvent(QDragMoveEvent *event) {
    event->acceptProposedAction();
    QWidget::dragMoveEvent(event);
}

void UI::PlayerWindow::dragLeaveEvent(QDragLeaveEvent *event) {
    event->accept();
    QWidget::dragLeaveEvent(event);
}

void UI::PlayerWindow::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        QStringList pathList;
        QList<QUrl> urlList = mimeData->urls();

        for (int i = 0; i < urlList.size(); ++i) {
            QFileInfo fileInfo(urlList.at(i).toLocalFile());
            if (fileInfo.isDir()) {
                appendDirectory(QDir(fileInfo.absoluteFilePath()), pathList);
            } else
                pathList.append(urlList.at(i).toLocalFile());
        }

        openFiles(pathList);
    }

    QWidget::dropEvent(event);
}

void UI::PlayerWindow::openFiles(const QStringList &paths) {
    QMimeDatabase mimeDatabase;
    for (auto it = paths.begin(); it != paths.end(); it++) {
        QMimeType mimeType = mimeDatabase.mimeTypeForFile(*it);
        if (mimeType.name().startsWith("audio")) {
            AudioTreeWidgetItem *item;
            item = new AudioTreeWidgetItem(*it);
            twTracks->addTopLevelItem(item);
            playlist->addMedia(item->getMediaContent());
            QApplication::instance()->processEvents();
        }
    }
}

void UI::PlayerWindow::appendDirectory(const QDir &dir, QStringList &paths) {
    QStringList files = dir.entryList();
    for (auto it = files.begin(); it != files.end(); it++) {
        QFileInfo fileInfo(dir, *it);
        if ((*it).compare(".") == 0 || (*it).compare("..") == 0)
            continue;
        if (fileInfo.isDir()) {
            appendDirectory(QDir(fileInfo.absoluteFilePath()), paths);
        } else {
            paths.append(fileInfo.absoluteFilePath());
        }
    }
}
