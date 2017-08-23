//
// Created by mohsen on 1/22/17.
//

#ifndef DSPLAYER_TREEVIEW_H
#define DSPLAYER_TREEVIEW_H


#include <QtWidgets/QTreeWidget>

namespace UI {
    class TreeView : public QTreeWidget {
    Q_OBJECT
    signals:

        void itemsMoved(QList<int> from, QList<int> to);

    public:
        TreeView(QWidget *parent = nullptr);

    protected:
        void dropEvent(QDropEvent *event) override;
    };
}
#endif //DSPLAYER_TREEVIEW_H
