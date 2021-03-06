//
// Created by mohsen on 1/14/17.
//

#include "SeekBar.h"

UI::SeekBar::SeekBar(QWidget *parent) : QProgressBar(parent) {
    setTextVisible(false);
    label = new QLabel(this);
    label->setText("");
    label->setVisible(false);

    auto lblPalette = label->palette();
    auto thisPalette = this->palette();
    label->setAutoFillBackground(true);
    auto labelColor = thisPalette.color(QPalette::Highlight);
    labelColor.setAlpha(100);
    lblPalette.setColor(label->backgroundRole(), labelColor);
    label->setPalette(lblPalette);
    label->setAlignment(Qt::AlignCenter);

    timer = new QTimer;
    timer->setInterval(1000);
    timer->setSingleShot(true);

    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerTimeOut()));
}

UI::SeekBar::~SeekBar() {
    delete timer;
    delete label;
}

void UI::SeekBar::mousePressEvent(QMouseEvent *event) {
    isDown = true;
    updateValue(event->x());
    QWidget::mousePressEvent(event);
}

void UI::SeekBar::mouseReleaseEvent(QMouseEvent *event) {
    isDown = false;
    QWidget::mouseReleaseEvent(event);
}

void UI::SeekBar::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget::mouseDoubleClickEvent(event);
}

void UI::SeekBar::mouseMoveEvent(QMouseEvent *event) {
    if (isDown) {
        updateValue(event->x());
    }
    QWidget::mouseMoveEvent(event);
}

#ifndef QT_NO_WHEELEVENT

void UI::SeekBar::wheelEvent(QWheelEvent *event) {
    QWidget::wheelEvent(event);
}

#endif

void UI::SeekBar::enterEvent(QEvent *event) {
    QWidget::enterEvent(event);
}

void UI::SeekBar::leaveEvent(QEvent *event) {
    QWidget::leaveEvent(event);
}

void UI::SeekBar::resizeEvent(QResizeEvent *event) {
    label->setGeometry((this->width() - label->width()) / 2, 0, label->width(), this->height());
    QWidget::resizeEvent(event);
}

void UI::SeekBar::updateValue(int x) {
    int value = x * maximum() / (this->width());
    if (value < minimum())
        value = minimum();
    if (value > maximum())
        value = maximum();
    setFocus();
    emit userChangedValue(value);
}

void UI::SeekBar::requestLabel(const QString &text) {
    label->setText(text);
    label->setFixedWidth(label->fontMetrics().width(text) + 20);
    label->setGeometry((this->width() - label->width()) / 2, 0, label->width(), this->height());
    label->setVisible(true);
    repaint();
    timer->start();
}

void UI::SeekBar::onTimerTimeOut() {
    label->setVisible(false);
}
