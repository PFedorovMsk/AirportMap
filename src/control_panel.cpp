#include "control_panel.h"
#include "ui_control_panel.h"

#include "custom_check_box.h"


ControlPanel::ControlPanel(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::ControlPanel)
{
    ui->setupUi(this);

    ui->btnAirportsColor->setColor(m_state.airportsColor);
    ui->btnAirportsFinancingColor->setColor(m_state.airportsFinancingColor);
    ui->btnAirportsTrafficColor->setColor(m_state.airportsTrafficColor);
    ui->btnHeliportsColor->setColor(m_state.heliportsColor);
}

ControlPanel::~ControlPanel()
{
    delete ui;
}

const StateOfParameters& ControlPanel::state() const
{
    return m_state;
}

void ControlPanel::setRegionsToTree(const TwoLevelTreeItems &data)
{
    for (int i = 0; i < data.topLevels.count(); i++) {
        QTreeWidgetItem *top = new QTreeWidgetItem({data.topLevels[i]});
        QList<QTreeWidgetItem*> children;
        for (int j = 0; j < data.childrens[i].count(); j++) {
            children.append(new QTreeWidgetItem({data.childrens[i][j]}));
        }
        top->addChildren(children);
        ui->treeRegions->addTopLevelItem(top);
    }

    for (int i = 0; i < ui->treeRegions->topLevelItemCount(); ++i) {
        treeWidgetItemAssignCheckBox(ui->treeRegions, ui->treeRegions->topLevelItem(i));
        for (int j = 0; j < ui->treeRegions->topLevelItem(i)->childCount(); ++j) {
            treeWidgetItemAssignCheckBox(ui->treeRegions, ui->treeRegions->topLevelItem(i)->child(j));
        }
    }
}

void ControlPanel::on_gbAirports_toggled(bool checked)
{
    if (m_state.showAirports == checked) {
        return;
    }
    m_state.showAirports = checked;
    emit stateChanged();
}

void ControlPanel::on_cbAirportsInternational_toggled(bool checked)
{
    if (m_state.showAirportsInternational == checked) {
        return;
    }
    m_state.showAirportsInternational = checked;
    emit stateChanged();
}

void ControlPanel::on_cbAirportsDomestic_toggled(bool checked)
{
    if (m_state.showAirportsDomestic == checked) {
        return;
    }
    m_state.showAirportsDomestic = checked;
    emit stateChanged();
}

void ControlPanel::on_cbAirportsRunwayCoverHard_toggled(bool checked)
{
    if (m_state.showAirportsWithHardCoverOfRunway == checked) {
        return;
    }
    m_state.showAirportsWithHardCoverOfRunway = checked;
    emit stateChanged();
}

void ControlPanel::on_cbAirportsRunwayCoverGround_toggled(bool checked)
{
    if (m_state.showAirportsWithGroundCoverOfRunway == checked) {
        return;
    }
    m_state.showAirportsWithGroundCoverOfRunway = checked;
    emit stateChanged();
}

void ControlPanel::on_cbAirportsRunwayType1_toggled(bool checked)
{
    if (m_state.showAirportsWithRunwayType1 == checked) {
        return;
    }
    m_state.showAirportsWithRunwayType1 = checked;
    emit stateChanged();
}

void ControlPanel::on_cbAirportsRunwayType2_toggled(bool checked)
{
    if (m_state.showAirportsWithRunwayType2 == checked) {
        return;
    }
    m_state.showAirportsWithRunwayType2 = checked;
    emit stateChanged();
}

void ControlPanel::on_cbAirportsRunwayType3_toggled(bool checked)
{
    if (m_state.showAirportsWithRunwayType3 == checked) {
        return;
    }
    m_state.showAirportsWithRunwayType3 = checked;
    emit stateChanged();
}

void ControlPanel::on_cbAirportsRunwayType4_toggled(bool checked)
{
    if (m_state.showAirportsWithRunwayType4 == checked) {
        return;
    }
    m_state.showAirportsWithRunwayType4 = checked;
    emit stateChanged();
}

void ControlPanel::on_cbAirportsRunwayType5_toggled(bool checked)
{
    if (m_state.showAirportsWithRunwayType5 == checked) {
        return;
    }
    m_state.showAirportsWithRunwayType5 = checked;
    emit stateChanged();
}

void ControlPanel::on_cbAirportsRunwayType6_toggled(bool checked)
{
    if (m_state.showAirportsWithRunwayType6 == checked) {
        return;
    }
    m_state.showAirportsWithRunwayType6 = checked;
    emit stateChanged();
}

void ControlPanel::on_cbAirportsRunwayNo_toggled(bool checked)
{
    if (m_state.showAirportsWithRunwayTypeNo == checked) {
        return;
    }
    m_state.showAirportsWithRunwayTypeNo = checked;
    emit stateChanged();
}

void ControlPanel::on_cbAirportsLightingConst_toggled(bool checked)
{
    if (m_state.showAirportsWithConstantLighting == checked) {
        return;
    }
    m_state.showAirportsWithConstantLighting = checked;
    emit stateChanged();
}

void ControlPanel::on_cbAirportsLightingOnRequest_toggled(bool checked)
{
    if (m_state.showAirportsWithLightingByRequest == checked) {
        return;
    }
    m_state.showAirportsWithLightingByRequest = checked;
    emit stateChanged();
}

void ControlPanel::on_cbAirportsLightingNo_toggled(bool checked)
{
    if (m_state.showAirportsWithoutLighting == checked) {
        return;
    }
    m_state.showAirportsWithoutLighting = checked;
    emit stateChanged();
}

void ControlPanel::on_cbAirportsFinancing_toggled(bool checked)
{
    if (m_state.showAirportsFinancing == checked) {
        return;
    }
    m_state.showAirportsFinancing = checked;
    emit stateChanged();
}

void ControlPanel::on_cbAirportsTraffic_toggled(bool checked)
{
    if (m_state.showAirportsTraffic == checked) {
        return;
    }
    m_state.showAirportsTraffic = checked;
    emit stateChanged();
}

void ControlPanel::on_gbHeliports_toggled(bool checked)
{
    if (m_state.showHeliports == checked) {
        return;
    }
    m_state.showHeliports = checked;
    emit stateChanged();
}

void ControlPanel::on_btnAirportsColor_clicked()
{
    if (m_state.airportsColor == ui->btnAirportsColor->color()) {
        return;
    }
    m_state.airportsColor = ui->btnAirportsColor->color();
    emit stateChanged();
}

void ControlPanel::on_btnAirportsFinancingColor_clicked()
{
    if (m_state.airportsFinancingColor == ui->btnAirportsFinancingColor->color()) {
        return;
    }
    m_state.airportsFinancingColor = ui->btnAirportsFinancingColor->color();
    emit stateChanged();
}

void ControlPanel::on_btnAirportsTrafficColor_clicked()
{
    if (m_state.airportsTrafficColor == ui->btnAirportsTrafficColor->color()) {
        return;
    }
    m_state.airportsTrafficColor = ui->btnAirportsTrafficColor->color();
    emit stateChanged();
}

void ControlPanel::on_btnHeliportsColor_clicked()
{
    if (m_state.heliportsColor == ui->btnHeliportsColor->color()) {
        return;
    }
    m_state.heliportsColor = ui->btnHeliportsColor->color();
    emit stateChanged();
}

void ControlPanel::on_cbAirportsOnlyFor_toggled(bool checked)
{
    //...
    emit stateChanged();
}
