#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H

#include <QCheckBox>
#include <QGroupBox>
#include <QWidget>


class ControlPanel : public QGroupBox
{
public:
    explicit ControlPanel(QWidget *parent = nullptr);
    ~ControlPanel() override;

private:
    void initControls();
    void initLayouts();

    QCheckBox *m_cbShowAirpots;
    QCheckBox *m_cbShowHeliports;
};

#endif // CONTROL_PANEL_H
