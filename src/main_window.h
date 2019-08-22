#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QGuiApplication>
#include <QMainWindow>
#include <QQuickWidget>

#include "src/control_panel.h"
#include "src/database_editor_panel.h"
#include "src/font_manager.h"
#include "src/graph_window.h"
#include "src/gui_config.h"
#include "src/query_maker.h"
#include "src/sql_query_model.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

signals:
    void clear();

private slots:
    void paintMainObjects();
    void paintAdditionalObjects();

    void paintGraphPopulation();
    void paintGraph();

private:
    void loadFonts();
    void initDatabase();
    void initMapScene();
    void initControlPanel();
    void initDatabaseEditor();
    void initLayouts();
    void initScreenRect();
    void initGraphWindow();
    void makeGraphData(const QVector<double> &xData, const QVector<double> &yData, QVector<double> &xResult,
                       QVector<double> &yResult, double xStep);

private slots:
    void insertRow();
    void removeRow();
    void changeTable(const QString &tableName);

private:
    QSqlDatabase         m_database;
    GraphWindow *        m_graphWindow;
    QQuickWidget *       m_mapScene;
    ControlPanel *       m_controlPanel;
    DatabaseEditorPanel *m_databaseEditorPanel;
    QSqlTableModel *     m_sqlTableModel;
    QTableView *         m_databaseView;

    QString m_databaseHostName;
    QString m_databaseDatabaseName;
    QString m_databaseUserName;
    QString m_databasePassword;
};

#endif // MAIN_WINDOW_H
