//
// Created by mohsen on 1/3/17.
//

#include <iostream>
#include "PlayerWindow.h"

void UI::PlayerWindow::onBtnPlayClicked() {

}

void UI::PlayerWindow::onBtnStopClicked() {

}

void UI::PlayerWindow::onBtnNextClicked() {

}

void UI::PlayerWindow::onBtnPrevClicked() {

}

void UI::PlayerWindow::onHsVolumeValueChanged() {
    std::cout << hsVolume->get_value() << std::endl;
}

void UI::PlayerWindow::onPbSeekChanged(double value) {
    pbSeek->set_fraction(value);
    pbSeek->requestLabel("HELLO LABEL");
}

UI::PlayerWindow::PlayerWindow() {
    //Create controls

    using namespace Gtk;

    btnPlay = new Button(Stock::MEDIA_PLAY);
    btnNext = new Button(Stock::MEDIA_NEXT);
    btnPrev = new Button(Stock::MEDIA_PREVIOUS);
    btnStop = new Button(Stock::MEDIA_STOP);
    hsVolume = new HScale(0, 100, 1);
    pbSeek = new SeekBar();

    vbMainContainer = new VBox();
    vbProgressContainer = new VBox();
    hbTopContainer = new HBox();

    //Init controls

    hbTopContainer->set_size_request(-1, 30);

    hsVolume->set_size_request(100, -1);
    hsVolume->set_draw_value(false);

    pbSeek->set_fraction(0.5);
    pbSeek->requestLabel("HELLO WORLD");

    //Init signals

    btnPlay->signal_clicked().connect(sigc::mem_fun(*this, &PlayerWindow::onBtnPlayClicked));
    btnNext->signal_clicked().connect(sigc::mem_fun(*this, &PlayerWindow::onBtnNextClicked));
    btnPrev->signal_clicked().connect(sigc::mem_fun(*this, &PlayerWindow::onBtnPrevClicked));
    btnStop->signal_clicked().connect(sigc::mem_fun(*this, &PlayerWindow::onBtnStopClicked));
    hsVolume->signal_value_changed().connect(sigc::mem_fun(*this, &PlayerWindow::onHsVolumeValueChanged));

    pbSeek->signal_changed().connect(sigc::mem_fun(*this, &PlayerWindow::onPbSeekChanged));

    //Arrange controls

    vbMainContainer->pack_start(*hbTopContainer, false, false);

//    vbProgressContainer->pack_start(*pbSeek, true, false, 10);

    hbTopContainer->pack_start(*btnPlay, false, false);
    hbTopContainer->pack_start(*btnNext, false, false);
    hbTopContainer->pack_start(*btnPrev, false, false);
    hbTopContainer->pack_start(*btnStop, false, false);
    hbTopContainer->pack_start(*pbSeek, true, true, 10);
    hbTopContainer->pack_end(*hsVolume, false, true);

    add(*vbMainContainer);
    set_position(Gtk::WindowPosition::WIN_POS_CENTER);
    set_default_size(800, 600);
    show_all();
}

UI::PlayerWindow::~PlayerWindow() {
    //destroy controls
    delete vbProgressContainer;
    delete hbTopContainer;
    delete vbMainContainer;
    delete btnPlay;
    delete btnNext;
    delete btnPrev;
    delete btnStop;
    delete hsVolume;
    delete pbSeek;
}
