//
// Created by mohsen on 1/22/17.
//

#include "TreeView.h"

UI::TreeView::TreeView(QWidget *parent) : QTreeWidget(parent) {
    this->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
    this->setDropIndicatorShown(true);
    this->setAcceptDrops(true);
    this->setDragEnabled(true);
    this->setDragDropMode(QAbstractItemView::DragDropMode::InternalMove);
    invisibleRootItem()->setFlags(invisibleRootItem()->flags() ^ Qt::ItemFlag::ItemIsDragEnabled);
}

void UI::TreeView::dropEvent(QDropEvent *event) {
    // get the list of the items that are about to be dragged
    QList<QTreeWidgetItem *> dragItems = selectedItems();

    // find out their row numbers before the drag
    QList<int> fromRows;
    QTreeWidgetItem *item;
            foreach(item, dragItems) fromRows.append(indexFromItem(item).row());

    // the default implementation takes care of the actual move inside the tree
    QTreeWidget::dropEvent(event);

    // query the indices of the dragged items again
    QList<int> toRows;
            foreach(item, dragItems) toRows.append(indexFromItem(item).row());

    // notify subscribers in some useful way
    emit itemsMoved(fromRows, toRows);
}
