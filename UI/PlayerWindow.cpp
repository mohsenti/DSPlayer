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

}

void UI::PlayerWindow::onBtnPrevClicked() {

}

void UI::PlayerWindow::onHsVolumeValueChanged(int value) {
    pbSeek->setValue(value);
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

    lwTracks = new QListWidget(this);

    //Init controls

    hsVolume->setFixedWidth(100);
    hsVolume->setRange(0, 100);
    hsVolume->setValue(50);

    pbSeek->setMinimumWidth(250);
    pbSeek->setRange(0, 100);
    pbSeek->setValue(50);
    pbSeek->setFormat("2:15");

    //Init signals

    connect(btnPlay, SIGNAL(clicked()), this, SLOT(onBtnPlayClicked()));
    connect(btnNext, SIGNAL(clicked()), this, SLOT(onBtnNextClicked()));
    connect(btnPrev, SIGNAL(clicked()), this, SLOT(onBtnPrevClicked()));
    connect(btnStop, SIGNAL(clicked()), this, SLOT(onBtnStopClicked()));
    connect(hsVolume, SIGNAL(valueChanged(int)), this, SLOT(onHsVolumeValueChanged(int)));

    //Arrange controls

    vbMainContainer->setAlignment(Qt::AlignmentFlag::AlignTop);
    vbMainContainer->addLayout(hbTopContainer);

    hbTopContainer->addWidget(btnPlay);
    hbTopContainer->addWidget(btnStop);
    hbTopContainer->addWidget(btnNext);
    hbTopContainer->addWidget(btnPrev);
    hbTopContainer->addWidget(pbSeek);
    hbTopContainer->addWidget(hsVolume);

    vbMainContainer->addWidget(lwTracks);

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
    delete lwTracks;

}
