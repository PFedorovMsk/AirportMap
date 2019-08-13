#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H

#include <QGroupBox>
#include "state_of_parameters.h"

#include <QSqlQueryModel>
#include <QSqlDatabase>


namespace Ui
{
class ControlPanel;
}

struct TwoLevelTreeItems {
    QVector<QString> topLevels;
    QVector<QVector<QString>> childrens;
};

class ControlPanel : public QGroupBox
{
    Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = nullptr);
    ~ControlPanel();

    const StateOfParameters& state() const;

    void setRegionsToTree(const TwoLevelTreeItems &data);

signals:
    void stateChanged();

private slots:
    void on_gbAirports_toggled(bool checked);
    void on_cbAirportsInternational_toggled(bool checked);
    void on_cbAirportsDomestic_toggled(bool checked);
    void on_cbAirportsRunwayCoverHard_toggled(bool checked);
    void on_cbAirportsRunwayCoverGround_toggled(bool checked);
    void on_cbAirportsRunwayType1_toggled(bool checked);
    void on_cbAirportsRunwayType2_toggled(bool checked);
    void on_cbAirportsRunwayType3_toggled(bool checked);
    void on_cbAirportsRunwayType4_toggled(bool checked);
    void on_cbAirportsRunwayType5_toggled(bool checked);
    void on_cbAirportsRunwayType6_toggled(bool checked);
    void on_cbAirportsRunwayNo_toggled(bool checked);
    void on_cbAirportsLightingConst_toggled(bool checked);
    void on_cbAirportsLightingOnRequest_toggled(bool checked);
    void on_cbAirportsLightingNo_toggled(bool checked);
    void on_cbAirportsFinancing_toggled(bool checked);
    void on_cbAirportsTraffic_toggled(bool checked);
    void on_gbHeliports_toggled(bool checked);
    void on_btnAirportsColor_clicked();
    void on_btnAirportsFinancingColor_clicked();
    void on_btnAirportsTrafficColor_clicked();
    void on_btnHeliportsColor_clicked();
    void on_cbAirportsOnlyFor_toggled(bool checked);


private:
    Ui::ControlPanel *ui;
    StateOfParameters m_state;
};


#endif // CONTROL_PANEL_H
