#ifndef MYCHECKBOX_H
#define MYCHECKBOX_H

#include <QCheckBox>
#include <QTreeWidget>
#include <QTreeWidgetItem>


class QTreeWidgetItem;


template <typename MyObject, typename WidgetType>
void traverseTreeWidgetItem(QTreeWidget *treeWidget, QTreeWidgetItem *treeItem, MyObject object)
{
    QTreeWidgetItem *childItem  = nullptr;
    QWidget *        itemWidget = nullptr;
    WidgetType *     widget     = nullptr;

    if (treeItem->childCount() > 0) {
        for (int i = 0; i < treeItem->childCount(); ++i) {
            childItem  = treeItem->child(i);
            itemWidget = treeWidget->itemWidget(childItem, 0);
            widget     = static_cast<WidgetType *>(itemWidget);
            if (widget && widget->isChecked()) {
                object->process(treeWidget, childItem);
                traverseTreeWidgetItem<MyObject, WidgetType>(treeWidget, childItem, object);
            }
        }
    } else {
        itemWidget = treeWidget->itemWidget(treeItem, 0);
        widget     = static_cast<WidgetType *>(itemWidget);
        if (widget && widget->isChecked()) {
            object->process(treeWidget, treeItem);
        }
    }
}


template <typename MyObject, typename WidgetType>
void traverseTreeWidget(QTreeWidget *treeWidget, MyObject object)
{
    QTreeWidgetItem *topItem = nullptr;

    for (int i = 0; i < treeWidget->topLevelItemCount(); ++i) {
        topItem = treeWidget->topLevelItem(i);
        traverseTreeWidgetItem<MyObject, WidgetType>(treeWidget, topItem, object);
    }
}


void treeWidgetItemAssignCheckBox(QTreeWidget *treeWidget, QTreeWidgetItem *treeItem);


class CustomCheckBox : public QCheckBox
{
    Q_OBJECT

public:
    CustomCheckBox(QTreeWidgetItem *item);

    QTreeWidgetItem *item() const;

private:
    QTreeWidgetItem *m_item;

    void setChildrenCheckedUnchecked(QTreeWidgetItem *item) const;
    void setParentChecked(QTreeWidgetItem *treeItem) const;
    void setParentCheckedUncheckedBasedOnSiblings(CustomCheckBox *checkbox) const;
};


#endif // MYCHECKBOX_H
