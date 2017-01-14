//
// Created by mohsen on 1/14/17.
//

#ifndef DSPLAYER_SEEKBAR_H
#define DSPLAYER_SEEKBAR_H


#include <QtGui/QProgressBar>
#include <QtGui/QWidget>
#include <QtGui/QLabel>

namespace UI {
    class SeekBar : public QProgressBar {
    Q_OBJECT

    public:
        explicit SeekBar(QWidget *parent = 0);

        virtual ~SeekBar();

    private:
        bool isDown = false;
        QLabel *label;

        void updateValue(int x);

    protected:
        virtual void mousePressEvent(QMouseEvent *event) override;

        virtual void mouseReleaseEvent(QMouseEvent *event) override;

        virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

        virtual void mouseMoveEvent(QMouseEvent *event) override;

#ifndef QT_NO_WHEELEVENT

        virtual void wheelEvent(QWheelEvent *event) override;

#endif

        virtual void enterEvent(QEvent *event) override;

        virtual void leaveEvent(QEvent *event) override;

        virtual void resizeEvent(QResizeEvent *event) override;

    signals:

        void userChangedValue(int value);
    };
}

#endif //DSPLAYER_SEEKBAR_H
