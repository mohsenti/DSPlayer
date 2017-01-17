//
// Created by mohsen on 1/17/17.
//

#ifndef DSPLAYER_AUDIOTREEWIDGETITEM_H
#define DSPLAYER_AUDIOTREEWIDGETITEM_H

#include <QtWidgets>

namespace UI {
    class AudioTreeWidgetItem : public QTreeWidgetItem {
    public:
        explicit AudioTreeWidgetItem(const QString &fileName);

    private:
        QString filename;

    };
}

#endif //DSPLAYER_AUDIOTREEWIDGETITEM_H
