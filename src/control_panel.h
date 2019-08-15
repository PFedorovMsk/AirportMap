#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H

#include "state_of_parameters.h"
#include <QGroupBox>

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QTreeWidget>
#include <QTreeWidgetItem>


namespace Ui
{
class ControlPanel;
}

struct TwoLevelTreeItems {
    QVector<QString>          topLevels;
    QVector<QVector<QString>> childrens;
};

class ControlPanel : public QGroupBox
{
    Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = nullptr);
    ~ControlPanel();

    const StateOfParameters &state() const;

    void setRegionsToTree(const TwoLevelTreeItems &data);

    void process(QTreeWidget *tree_widget, QTreeWidgetItem *tree_item);

signals:
    void mainStateChanged();
    void additionalStateChanged();

private slots:
    void on_cbAirports_toggled(bool checked);
    void on_cbHeliports_toggled(bool checked);
    void on_cbCities_toggled(bool checked);
    void on_cbFinancing_toggled(bool checked);
    void on_btnAirportsColor_clicked();
    void on_btnHeliportsColor_clicked();
    void on_btnCitiesColor_clicked();
    void on_btnFinancingColor_clicked();
    void on_cbInternational_toggled(bool checked);
    void on_cbDomestic_toggled(bool checked);
    void on_cbRunwayCoverHard_toggled(bool checked);
    void on_cbRunwayCoverGround_toggled(bool checked);
    void on_cbRunwayType1_toggled(bool checked);
    void on_cbRunwayType2_toggled(bool checked);
    void on_cbRunwayType3_toggled(bool checked);
    void on_cbRunwayType4_toggled(bool checked);
    void on_cbRunwayType5_toggled(bool checked);
    void on_cbRunwayType6_toggled(bool checked);
    void on_cbRunwayNo_toggled(bool checked);
    void on_cbBudget_toggled(bool checked);
    void on_cbExtraBudget_toggled(bool checked);
    void on_cbOnlyFor_toggled(bool checked);
    void on_btnUpdate_clicked();

private:
    Ui::ControlPanel *ui;
    StateOfParameters m_state;
};


#endif // CONTROL_PANEL_H
