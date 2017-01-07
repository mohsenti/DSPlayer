//
// Created by mohsen on 1/3/17.
//

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

}

UI::PlayerWindow::PlayerWindow() {
    //Create controls

    using namespace Gtk;
    btnPlay = new Button(Stock::MEDIA_PLAY);
    btnNext = new Button(Stock::MEDIA_NEXT);
    btnPrev = new Button(Stock::MEDIA_PREVIOUS);
    btnStop = new Button(Stock::MEDIA_STOP);
    hsVolume = new HScale(0, 101, 1);
    pbSeek = new ProgressBar();

    vbMainContainer = new VBox();
    vbProgressContainer = new VBox();
    hbTopContainer = new HBox();
    //Init controls
    hbTopContainer->set_size_request(-1, 30);
    hsVolume->set_size_request(100, -1);
    hsVolume->set_draw_value(false);
    pbSeek->set_fraction(0.5);
    //Init signals
    //Arrange controls
    vbMainContainer->pack_start(*hbTopContainer, false, false);

    vbProgressContainer->pack_start(*pbSeek, true, false, 10);

    hbTopContainer->pack_start(*btnPlay, false, false);
    hbTopContainer->pack_start(*btnNext, false, false);
    hbTopContainer->pack_start(*btnPrev, false, false);
    hbTopContainer->pack_start(*btnStop, false, false);
    hbTopContainer->pack_start(*vbProgressContainer, true, true, 10);
    hbTopContainer->pack_end(*hsVolume, false, true);

    add(vbMainContainer);
    set_position(Gtk::WindowPosition::WIN_POS_CENTER);
    set_default_size(800, 600);
    show_all();
}

UI::PlayerWindow::~PlayerWindow() {
    //destroy controls
    delete btnPlay;
    delete btnNext;
    delete btnPrev;
    delete btnStop;
    delete hsVolume;
    delete pbSeek;
}
