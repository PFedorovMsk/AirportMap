#include "src/custom_check_box.h"


void treeWidgetItemAssignCheckBox(QTreeWidget *treeWidget, QTreeWidgetItem *treeItem)
{
    CustomCheckBox *checkBox = new CustomCheckBox(treeItem);
    treeWidget->setItemWidget(treeItem, 0, checkBox);
}


CustomCheckBox::CustomCheckBox(QTreeWidgetItem *item)
    : QCheckBox(item->treeWidget())
{
    m_item = item;
    setText(m_item->text(0));
    m_item->setText(0, "");

    connect(this, &CustomCheckBox::clicked, this, [&]() {
        setChildrenCheckedUnchecked(m_item);
        if (isChecked()) {
            setParentChecked(m_item);
        }
        setParentCheckedUncheckedBasedOnSiblings(this);
    });
}

QTreeWidgetItem *CustomCheckBox::item() const
{
    return m_item;
}

void CustomCheckBox::setChildrenCheckedUnchecked(QTreeWidgetItem *item) const
{
    QWidget *        itemWidget   = nullptr;
    QTreeWidget *    treeWidget   = nullptr;
    QTreeWidgetItem *childItem    = nullptr;
    CustomCheckBox * checkbox     = nullptr;
    CustomCheckBox * itemCheckbox = nullptr;

    treeWidget = item->treeWidget();
    checkbox   = static_cast<CustomCheckBox *>(treeWidget->itemWidget(item, 0));

    for (int i = 0; i < item->childCount(); ++i) {
        childItem    = item->child(i);
        itemWidget   = treeWidget->itemWidget(childItem, 0);
        itemCheckbox = static_cast<CustomCheckBox *>(itemWidget);
        itemCheckbox->setChecked(checkbox->isChecked());
        setChildrenCheckedUnchecked(childItem);
    }
}

void CustomCheckBox::setParentChecked(QTreeWidgetItem *treeItem) const
{
    QWidget *    parentWidget = nullptr;
    QTreeWidget *treeWidget   = treeItem->treeWidget();
    ;
    QTreeWidgetItem *parentItem     = treeItem->parent();
    CustomCheckBox * parentCheckbox = nullptr;

    if (parentItem) {
        parentWidget   = treeWidget->itemWidget(parentItem, 0);
        parentCheckbox = static_cast<CustomCheckBox *>(parentWidget);
        parentCheckbox->setChecked(true);
        setParentChecked(parentItem);
    }
}

void CustomCheckBox::setParentCheckedUncheckedBasedOnSiblings(CustomCheckBox *checkbox) const
{
    QWidget *        itemWidget       = nullptr;
    QWidget *        parentItemWidget = nullptr;
    QTreeWidgetItem *parentItem       = checkbox->m_item->parent();
    QTreeWidgetItem *childItem        = nullptr;
    QTreeWidget *    treeWidget       = nullptr;
    CustomCheckBox * childCheckbox    = nullptr;
    CustomCheckBox * parentCheckbox   = nullptr;

    if (parentItem) {
        treeWidget                      = parentItem->treeWidget();
        parentItemWidget                = treeWidget->itemWidget(parentItem, 0);
        parentCheckbox                  = static_cast<CustomCheckBox *>(parentItemWidget);
        const int childCount            = parentItem->childCount();
        int       checkedUncheckedCount = 0;
        for (int i = 0; i < childCount; ++i) {
            childItem     = parentItem->child(i);
            itemWidget    = treeWidget->itemWidget(childItem, 0);
            childCheckbox = static_cast<CustomCheckBox *>(itemWidget);
            if (childCheckbox->isChecked() == checkbox->isChecked()) {
                ++checkedUncheckedCount;
            }
        }
        if (checkedUncheckedCount == childCount) {
            parentCheckbox->setChecked(checkbox->isChecked());
            setParentCheckedUncheckedBasedOnSiblings(parentCheckbox);
        }
    }
}
