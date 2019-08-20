#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QGuiApplication>
#include <QMainWindow>
#include <QQuickWidget>

#include "src/control_panel.h"
#include "src/font_manager.h"
#include "src/graph_window.h"
#include "src/gui_config.h"
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
    void initDatabase();
    void loadFonts();
    void initMapScene();
    void initControlPanel();
    void initLayouts();
    void initScreenRect();
    void initGraphWindow();

    void makeCitiesQuery(const StateOfParameters &state, QString &citiesQuery, QString &stopsQuery, QString &portsQuery,
                         QString &trainStationsQuery);
    void makeFinancingQuery(const StateOfParameters &state, QString &financingQuery);
    void makeAirpotsAndHeliportsQuery(const StateOfParameters &state, QString &airportsQuery, QString &heliportsQuery);

private:
    QSqlDatabase  m_database;
    GraphWindow * m_graphWindow;
    QQuickWidget *m_mapScene;
    ControlPanel *m_controlPanel;

    QString m_databaseHostName;
    QString m_databaseDatabaseName;
    QString m_databaseUserName;
    QString m_databasePassword;
};

#endif // MAIN_WINDOW_H
