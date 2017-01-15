//
// Created by mohsen on 1/3/17.
//

#include <iostream>
#include <QtGui/QDesktopWidget>
#include <QtGui/QStyle>
#include <QtGui/QApplication>
#include <QDropEvent>
#include <QUrl>
#include <QDir>
#include <QDebug>
#include <QtGui/QFileDialog>
#include "PlayerWindow.h"

void UI::PlayerWindow::onBtnPlayClicked() {

}

void UI::PlayerWindow::onBtnStopClicked() {

}

void UI::PlayerWindow::onBtnNextClicked() {
    if (twTracks->currentIndex().row() < twTracks->topLevelItemCount() - 1)
        twTracks->setCurrentIndex(twTracks->indexBelow(twTracks->currentIndex()));
}

void UI::PlayerWindow::onBtnPrevClicked() {
    if (twTracks->currentIndex().row() > 0)
        twTracks->setCurrentIndex(twTracks->indexAbove(twTracks->currentIndex()));
}

void UI::PlayerWindow::onBtnRepeatToggled(bool checked) {

}

void UI::PlayerWindow::onBtnShuffleToggled(bool checked) {

}

void UI::PlayerWindow::onHsVolumeValueChanged(int value) {
    pbSeek->setValue(value);
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

}

void UI::PlayerWindow::onRemoveMenuTriggered(bool checked) {

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
    btnPrev = new QPushButton(QIcon::fromTheme("media-skip-backward"), "", this);
    btnNext = new QPushButton(QIcon::fromTheme("media-skip-forward"), "", this);
    btnStop = new QPushButton(QIcon::fromTheme("media-playback-stop"), "", this);
    btnShuffle = new QPushButton(QIcon::fromTheme("media-playlist-shuffle"), "", this);
    btnRepeat = new QPushButton(QIcon::fromTheme("media-playlist-repeat"), "", this);
    hsVolume = new QSlider(Qt::Horizontal, this);
    pbSeek = new SeekBar(this);

    twTracks = new QTreeWidget(this);

    //Init controls

    btnShuffle->setCheckable(true);
    btnRepeat->setCheckable(true);

    hsVolume->setFixedWidth(100);
    hsVolume->setRange(0, 100);
    hsVolume->setValue(50);

    pbSeek->setMinimumWidth(250);
    pbSeek->setRange(0, 100);
    pbSeek->setValue(50);
    pbSeek->setFormat("2:15");

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

QTreeWidgetItem *UI::PlayerWindow::createListItem(const QString &title, const QString &duration, const QString &album) {
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, title);
    item->setText(1, duration);
    item->setText(2, album);
    return item;
}

void UI::PlayerWindow::openFiles(const QStringList &paths) {
    for (auto it = paths.begin(); it != paths.end(); it++) {
        twTracks->addTopLevelItem(createListItem(*it, "", ""));
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
