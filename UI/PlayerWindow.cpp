//
// Created by mohsen on 1/3/17.
//

#include "PlayerWindow.h"
#include <sstream>
#include <Core/CoreTypes.h>

void UI::PlayerWindow::onPlayTriggered() {
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

void UI::PlayerWindow::onStopTriggered() {
    if (player->state() == QMediaPlayer::PlayingState || player->state() == QMediaPlayer::PausedState)
        player->stop();
}

void UI::PlayerWindow::onNextTriggered() {
    if (playlist->mediaCount() == 0)
        return;
    playlist->next();
}

void UI::PlayerWindow::onPrevTriggered() {
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
        pbSeek->requestLabel(Core::formatSecondsToTime(value / 1000, true).c_str());
    }
}

void UI::PlayerWindow::onPlaylistCurrentIndexChanged(int index) {
    if (index == -1 && btnRepeat->isChecked()) {
        playlist->next();
        index = 0;
        player->play();
    }
    AudioTreeWidgetItem *audioItem = (AudioTreeWidgetItem *) tvTracks->topLevelItem(playlist->previousIndex());
    if (audioItem != nullptr) {
        updateAudioItemIcon(audioItem, QMediaPlayer::State::StoppedState);
    }
    audioItem = (AudioTreeWidgetItem *) tvTracks->topLevelItem(index);
    if (audioItem != nullptr) {
        pbSeek->setValue(0);
        pbSeek->setRange(0, audioItem->getDuration());
        updateAudioItemIcon(audioItem, player->state());
    }
    tvTracks->setCurrentItem(audioItem);
}

void UI::PlayerWindow::onPlayerPositionChanged(qint64 position) {
    pbSeek->setValue((int) position);
}

void UI::PlayerWindow::onPlayerStateChanged(QMediaPlayer::State newState) {
    int index = playlist->currentIndex();
    if (index >= 0) {
        AudioTreeWidgetItem *item = (AudioTreeWidgetItem *) tvTracks->topLevelItem(index);
        if (item == nullptr)
            return;
        updateAudioItemIcon(item, newState);
    }

    switch (newState) {
        case QMediaPlayer::State::StoppedState:
            trayIcon->setIcon(QIcon::fromTheme("media-playback-stop"));
            btnPlay->setIcon(QIcon::fromTheme("media-playback-start"));
            break;
        case QMediaPlayer::State::PausedState:
            trayIcon->setIcon(QIcon::fromTheme("media-playback-pause"));
            btnPlay->setIcon(QIcon::fromTheme("media-playback-start"));
            break;
        case QMediaPlayer::State::PlayingState:
            trayIcon->setIcon(QIcon::fromTheme("media-playback-start"));
            btnPlay->setIcon(QIcon::fromTheme("media-playback-pause"));
            break;
    }
}

void UI::PlayerWindow::onPlaylistMediaRemoved(int start, int end) {
    for (int i = start; i <= end; i++) {
        auto item = tvTracks->topLevelItem(start);
        delete item;
    }
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
    auto list = tvTracks->selectedItems();
    for (auto it = list.begin(); it != list.end(); it++) {
        int index = tvTracks->indexOfTopLevelItem(*it);
        playlist->removeMedia(index);
    }
}

void UI::PlayerWindow::onTvTracksItemActivated(QTreeWidgetItem *item, int column) {
    int index = tvTracks->indexOfTopLevelItem(item);
    if (index != playlist->currentIndex()) {
        updateAudioItemIcon((AudioTreeWidgetItem *) tvTracks->topLevelItem(playlist->currentIndex()),
                            QMediaPlayer::State::StoppedState);
        playlist->setCurrentIndex(index);
        player->play();
    } else {
        switch (player->state()) {
            case QMediaPlayer::State::StoppedState:
            case QMediaPlayer::State::PausedState:
                player->play();
                break;
            case QMediaPlayer::State::PlayingState:
                player->pause();
                break;
        }
    }
}

void UI::PlayerWindow::onTvItemsMoved(QList<int> from, QList<int> to) {
    playlist->blockSignals(true);
    for (int i = 0; i < from.count(); i++) {
        playlist->moveMedia(from.at(i), to.at(i));
    }
    playlist->blockSignals(false);
}

void UI::PlayerWindow::onTvTracksShowContextMenu(const QPoint &point) {
    QPoint globalPoint = tvTracks->mapToGlobal(point);
    QMenu twMenu;
    if (tvTracks->selectedItems().size() > 0) {
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

void UI::PlayerWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
        case QSystemTrayIcon::ActivationReason::Trigger:
            if (this->isVisible())
                this->hide();
            else this->show();
            break;
    }
}

UI::PlayerWindow::PlayerWindow(InstanceCommunicate &communicate, QWidget *parent) : QWidget(parent),
                                                                                    communicate(communicate) {
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

    tvTracks = new TreeView(this);

    trayIcon = new QSystemTrayIcon(this);
    trayIconMenu = new QMenu(this);

    instanceRequestTimer = new QTimer;

    worker = new CommunicateThread(communicate);

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

    tvTracks->setColumnCount(4);
    QStringList labels;
    labels << "State" << "Track" << "Duration" << "Album";
    tvTracks->setHeaderLabels(labels);
    tvTracks->setContextMenuPolicy(Qt::CustomContextMenu);

    prepareTrayIconContextMenu();
    trayIcon->setIcon(QIcon::fromTheme("media-playback-stop"));
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->show();

    instanceRequestTimer->setInterval(1000);
    instanceRequestTimer->setSingleShot(true);

    //Init signals

    connect(btnPlay, SIGNAL(clicked()), this, SLOT(onPlayTriggered()));
    connect(btnNext, SIGNAL(clicked()), this, SLOT(onNextTriggered()));
    connect(btnPrev, SIGNAL(clicked()), this, SLOT(onPrevTriggered()));
    connect(btnStop, SIGNAL(clicked()), this, SLOT(onStopTriggered()));
    connect(btnRepeat, SIGNAL(toggled(bool)), this, SLOT(onBtnRepeatToggled(bool)));
    connect(btnShuffle, SIGNAL(toggled(bool)), this, SLOT(onBtnShuffleToggled(bool)));
    connect(hsVolume, SIGNAL(valueChanged(int)), this, SLOT(onHsVolumeValueChanged(int)));
    connect(tvTracks, SIGNAL(customContextMenuRequested(
                                     const QPoint&)), this, SLOT(onTvTracksShowContextMenu(
                                                                         const QPoint&)));
    connect(tvTracks, SIGNAL(itemActivated(QTreeWidgetItem * , int)), this,
            SLOT(onTvTracksItemActivated(QTreeWidgetItem * , int)));
    connect(tvTracks, SIGNAL(itemsMoved(QList<int>, QList<int>)), this, SLOT(onTvItemsMoved(QList<int>, QList<int>)));

    connect(pbSeek, SIGNAL(userChangedValue(int)), this, SLOT(onPbUserChangeValue(int)));

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this,
            SLOT(onTrayIconActivated(QSystemTrayIcon::ActivationReason)));

    connect(instanceRequestTimer, SIGNAL(timeout()), this, SLOT(onInstanceRequestTimerTimeOut()));
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

    vbMainContainer->addWidget(tvTracks);

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
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(onPlayerStateChanged(QMediaPlayer::State)));
    connect(playlist, SIGNAL(currentIndexChanged(int)), this, SLOT(onPlaylistCurrentIndexChanged(int)));
    connect(playlist, SIGNAL(mediaRemoved(int, int)), this, SLOT(onPlaylistMediaRemoved(int, int)));

    QObject::connect(worker, SIGNAL(messageReceived(
                                            const InstanceCommunicateMessage&)),
                     this, SLOT(onMessageReceived(
                                        const InstanceCommunicateMessage&)));
    worker->start();

    instanceRequestInTime = true;
    instanceRequestTimer->start();

    string appDir = Core::getHomeDirectory() + ".DSPlayer/";
    restoreApplicationState(QString::fromStdString(appDir + "tmp.pl"));
}

UI::PlayerWindow::~PlayerWindow() {
    string appDir = Core::getHomeDirectory() + ".DSPlayer/";
    saveApplicationState(QString::fromStdString(appDir + "tmp.pl"));
    //destroy controls

    delete instanceRequestTimer;
    delete playlist;
    delete player;

    delete hbTopContainer;
    delete vbMainContainer;
    delete btnPlay;
    delete btnNext;
    delete btnPrev;
    delete btnStop;
    delete hsVolume;
    delete pbSeek;
    delete tvTracks;

    delete trayIconMenu;
    delete trayIcon;
    delete worker;
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
            tvTracks->addTopLevelItem(item);
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

void UI::PlayerWindow::savePlaylist(const QString &fileName) {
    QFile file(fileName);
    file.open(QFile::OpenModeFlag::WriteOnly);
    std::stringstream stream;
    for (int i = 0; i < tvTracks->topLevelItemCount(); ++i) {
        AudioTreeWidgetItem *item = (AudioTreeWidgetItem *) tvTracks->topLevelItem(i);
        stream << item->getFileName().toStdString() << "\r\n";
    }
    file.write(stream.str().c_str());
    file.close();
}

void UI::PlayerWindow::restorePlaylist(const QString &fileName) {
    QFile file(fileName);
    file.open(QFile::OpenModeFlag::ReadOnly);
    QStringList paths;
    while (!file.atEnd()) {
        auto data = file.readLine();
        paths.append(QString::fromLocal8Bit(data.remove(data.lastIndexOf('\r'), 2)));
    }
    file.close();
    openFiles(paths);
}

void UI::PlayerWindow::updateAudioItemIcon(UI::AudioTreeWidgetItem *item, QMediaPlayer::State newState) {
    if (item == nullptr)
        return;
    switch (newState) {
        case QMediaPlayer::State::StoppedState:
            item->setIcon(QIcon());
            break;
        case QMediaPlayer::State::PlayingState:
            item->setIcon(QIcon::fromTheme("media-playback-start"));
            break;
        case QMediaPlayer::State::PausedState:
            item->setIcon(QIcon::fromTheme("media-playback-pause"));
            break;
    }
}

void UI::PlayerWindow::saveApplicationState(const QString &fileName) {
    Core::ApplicationState state;
    state.playerState = 0; // future use
    player->pause();
    state.currentItemIndex = playlist->currentIndex();
    state.volume = hsVolume->value();
    state.seekBarPosition = pbSeek->value();
    state.playlistItemsCount = tvTracks->topLevelItemCount(); // future use
    state.shuffle = btnShuffle->isChecked();
    state.repeat = btnRepeat->isChecked();

    QFile file(fileName);
    file.open(QFile::OpenModeFlag::WriteOnly);
    std::stringstream stream;
    for (int i = 0; i < tvTracks->topLevelItemCount(); ++i) {
        AudioTreeWidgetItem *item = (AudioTreeWidgetItem *) tvTracks->topLevelItem(i);
        stream << item->getFileName().toStdString() << "\r\n";
    }
    file.write((char *) &state, sizeof(Core::ApplicationState));
    file.write(stream.str().c_str());
    file.close();

}

void UI::PlayerWindow::restoreApplicationState(const QString &fileName) {
    Core::ApplicationState state;
    QFile file(fileName);
    if (!file.exists())
        return;
    file.open(QFile::OpenModeFlag::ReadOnly);
    QStringList paths;
    file.read((char *) &state, sizeof(Core::ApplicationState));
    while (!file.atEnd()) {
        auto data = file.readLine();
        paths.append(QString::fromLocal8Bit(data.remove(data.lastIndexOf('\r'), 2)));
    }
    file.close();
    openFiles(paths);
    playlist->setCurrentIndex(state.currentItemIndex);
    player->setPosition(state.seekBarPosition);
    hsVolume->setValue(state.volume);
    btnRepeat->setChecked(state.repeat);
    btnShuffle->setChecked(state.shuffle);
}

void UI::PlayerWindow::prepareTrayIconContextMenu() {
    QAction *action;
    action = trayIconMenu->addAction("Play/Pause");
    connect(action, SIGNAL(triggered(bool)), this, SLOT(onPlayTriggered()));
    action = trayIconMenu->addAction("Stop");
    connect(action, SIGNAL(triggered(bool)), this, SLOT(onStopTriggered()));
    action = trayIconMenu->addAction("Next");
    connect(action, SIGNAL(triggered(bool)), this, SLOT(onNextTriggered()));
    action = trayIconMenu->addAction("Prev");
    connect(action, SIGNAL(triggered(bool)), this, SLOT(onPrevTriggered()));
    trayIconMenu->addSeparator();
    action = trayIconMenu->addAction("Quit");
    connect(action, SIGNAL(triggered(bool)), this, SLOT(onQuitMenuTriggered(bool)));
}

void UI::PlayerWindow::otherInstanceRequestAddFile(string fileName) {
    QMimeDatabase mimeDatabase;
    QString qFileName = QString::fromStdString(fileName);
    QMimeType mimeType = mimeDatabase.mimeTypeForFile(qFileName);
    if (mimeType.name().startsWith("audio")) {
        AudioTreeWidgetItem *item;
        item = new AudioTreeWidgetItem(qFileName);
        if (!instanceRequestInTime) {
            playlist->clear();
        }
        tvTracks->addTopLevelItem(item);
        playlist->addMedia(item->getMediaContent());
        QApplication::instance()->processEvents();
    }
    instanceRequestInTime = true;
    instanceRequestTimer->start();
}

void UI::PlayerWindow::onInstanceRequestTimerTimeOut() {
    instanceRequestInTime = false;
}

void UI::PlayerWindow::onMessageReceived(const InstanceCommunicateMessage &message) {
    this->otherInstanceRequestAddFile(message.message);
}