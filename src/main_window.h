#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QGuiApplication>
#include <QMainWindow>
#include <QQuickWidget>

#include "src/control_panel.h"
#include "src/font_manager.h"
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
    void paintAirportsAndHeliports();
    void paintCities();

private:
    void loadFonts();
    void initControls();
    void initLayouts();

private:
    QQuickWidget *m_mapScene;
    ControlPanel *m_controlPanel;
    QSqlDatabase  m_database;
};

#endif // MAIN_WINDOW_H
