#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QGuiApplication>
#include <QMainWindow>
#include <QQuickWidget>

#include "src/control_panel.h"
#include "src/font_manager.h"
#include "src/gui_config.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

signals:
    void clear();

private slots:
    void onClear();
    void test();

private:
    void loadFonts();
    void initControls();
    void initLayouts();
    void addCircle(QVariant latitude, QVariant longitude, QVariant color, QVariant borderColor, QVariant radius);

private:
    QQuickWidget *m_mapScene;
    ControlPanel *m_controlPanel;
};

#endif // MAIN_WINDOW_H
