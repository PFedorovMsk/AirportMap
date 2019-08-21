#include "database_editor_panel.h"
#include "ui_database_editor_panel.h"


DatabaseEditorPanel::DatabaseEditorPanel(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::DatabaseEditorPanel)
{
    ui->setupUi(this);
}

DatabaseEditorPanel::~DatabaseEditorPanel()
{
    delete ui;
}

void DatabaseEditorPanel::setTablesList(const QStringList &list)
{
    ui->cbTablesList->clear();
    ui->cbTablesList->addItems(list);
    ui->cbTablesList->setCurrentIndex(0);
}

void DatabaseEditorPanel::on_cbTablesList_currentTextChanged(const QString &value)
{
    emit tableListChanged(value);
}

void DatabaseEditorPanel::on_btnInsertRow_clicked()
{
    emit insert();
}

void DatabaseEditorPanel::on_btnRemoveRow_clicked()
{
    emit remove();
}

void DatabaseEditorPanel::on_btnUndo_clicked()
{
    emit undo();
}

void DatabaseEditorPanel::on_btnSave_clicked()
{
    emit save();
}
