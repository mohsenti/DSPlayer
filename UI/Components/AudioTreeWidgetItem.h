//
// Created by mohsen on 1/17/17.
//

#ifndef DSPLAYER_AUDIOTREEWIDGETITEM_H
#define DSPLAYER_AUDIOTREEWIDGETITEM_H

#include <QtWidgets>
#include <QtMultimedia/QMediaContent>

namespace UI {
    class AudioTreeWidgetItem : public QTreeWidgetItem {
    public:
        explicit AudioTreeWidgetItem(const QString &fileName);

        QMediaContent getMediaContent() const;

        int getDuration();
        QString getFileName();
    private:
        QString filename;
        int duration;

    };
}

#endif //DSPLAYER_AUDIOTREEWIDGETITEM_H
