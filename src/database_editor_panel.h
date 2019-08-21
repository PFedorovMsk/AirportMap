#ifndef DATABASE_EDITOR_PANEL_H
#define DATABASE_EDITOR_PANEL_H

#include <QGroupBox>

namespace Ui
{
class DatabaseEditorPanel;
}


class DatabaseEditorPanel : public QGroupBox
{
    Q_OBJECT

public:
    explicit DatabaseEditorPanel(QWidget *parent = nullptr);
    ~DatabaseEditorPanel();

    void setTablesList(const QStringList &list);

signals:
    void tableListChanged(const QString &value);
    void insert();
    void remove();
    void undo();
    void save();

private slots:
    void on_cbTablesList_currentTextChanged(const QString &value);
    void on_btnInsertRow_clicked();
    void on_btnRemoveRow_clicked();
    void on_btnUndo_clicked();
    void on_btnSave_clicked();

private:
    Ui::DatabaseEditorPanel *ui;
};


#endif // DATABASE_EDITOR_PANEL_H
