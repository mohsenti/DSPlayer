//
// Created by mohsen on 1/3/17.
//

#include <iostream>
#include <QtGui/QDesktopWidget>
#include <QtGui/QStyle>
#include <QtGui/QApplication>
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

void UI::PlayerWindow::onHsVolumeValueChanged(int value) {
    pbSeek->setValue(value);
}

void UI::PlayerWindow::twTracksShowContextMenu(const QPoint &point) {
    QPoint globalPoint = twTracks->mapToGlobal(point);
    QMenu twMenu;
    if (twTracks->selectedItems().size() > 0) {
        twMenu.addAction("Remove");
        twMenu.addSeparator();
    }
    twMenu.addAction("Add File");
    twMenu.addAction("Add Folder");
    twMenu.addSeparator();
    twMenu.addAction("Quit");
    QAction *selectedItem = twMenu.exec(globalPoint);
}

UI::PlayerWindow::PlayerWindow(QWidget *parent) : QWidget(parent) {
    //Create controls

    vbMainContainer = new QVBoxLayout();
    hbTopContainer = new QHBoxLayout();

    btnPlay = new QPushButton(QIcon::fromTheme("media-playback-start"), "", this);
    btnPrev = new QPushButton(QIcon::fromTheme("media-skip-backward"), "", this);
    btnNext = new QPushButton(QIcon::fromTheme("media-skip-forward"), "", this);
    btnStop = new QPushButton(QIcon::fromTheme("media-playback-stop"), "", this);
    hsVolume = new QSlider(Qt::Horizontal, this);
    pbSeek = new SeekBar(this);

    twTracks = new QTreeWidget(this);

    //Init controls

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
    hbTopContainer->addWidget(pbSeek);
    hbTopContainer->addWidget(hsVolume);

    vbMainContainer->addWidget(twTracks);

    setLayout(vbMainContainer);

    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(),
                                          QApplication::desktop()->availableGeometry()));
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

QTreeWidgetItem *UI::PlayerWindow::createListItem(const QString &title, const QString &duration, const QString &album) {
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, title);
    item->setText(1, duration);
    item->setText(2, album);
    return item;
}
