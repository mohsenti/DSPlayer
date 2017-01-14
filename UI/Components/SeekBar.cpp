//
// Created by mohsen on 1/14/17.
//

#include "SeekBar.h"
#include <QMouseEvent>
#include <QDebug>
#include <QStyle>

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
}

UI::SeekBar::~SeekBar() {}

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

void UI::SeekBar::wheelEvent(QWheelEvent *event) {
    QWidget::wheelEvent(event);
}

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
    int value = x * 100 / (this->width());
    setValue(value);

    label->setText(QString::number(value));

    label->setGeometry((this->width() - label->width()) / 2, 0, label->width(), this->height());
    label->setVisible(true);

    emit userChangedValue(value);
}
