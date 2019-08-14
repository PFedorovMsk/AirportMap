#include "control_panel.h"
#include "ui_control_panel.h"

#include "custom_check_box.h"


ControlPanel::ControlPanel(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::ControlPanel)
{
    ui->setupUi(this);

    ui->btnAirportsColor->setColor(m_state.airportsColor);
    ui->btnHeliportsColor->setColor(m_state.heliportsColor);
    ui->btnCitiesColor->setColor(m_state.citiesColor);
    ui->btnFinancingColor->setColor(m_state.financingColor);
    ui->btnTrafficColor->setColor(m_state.trafficColor);
}

ControlPanel::~ControlPanel()
{
    delete ui;
}

const StateOfParameters &ControlPanel::state() const
{
    return m_state;
}

void ControlPanel::setRegionsToTree(const TwoLevelTreeItems &data)
{
    for (int i = 0; i < data.topLevels.count(); i++) {
        QTreeWidgetItem *        top = new QTreeWidgetItem({data.topLevels[i]});
        QList<QTreeWidgetItem *> children;
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

void ControlPanel::on_cbAirports_toggled(bool checked)
{
    if (m_state.airports == checked) {
        return;
    }
    m_state.airports = checked;
    emit stateChanged();
}

void ControlPanel::on_cbHeliports_toggled(bool checked)
{
    if (m_state.heliports == checked) {
        return;
    }
    m_state.heliports = checked;
    emit stateChanged();
}

void ControlPanel::on_cbCities_toggled(bool checked)
{
    if (m_state.cities == checked) {
        return;
    }
    m_state.cities = checked;
    emit stateChanged();
}

void ControlPanel::on_cbFinancing_toggled(bool checked)
{
    if (m_state.financing == checked) {
        return;
    }
    m_state.financing = checked;
    emit stateChanged();
}

void ControlPanel::on_cbTraffic_toggled(bool checked)
{
    if (m_state.traffic == checked) {
        return;
    }
    m_state.traffic = checked;
    emit stateChanged();
}

void ControlPanel::on_btnAirportsColor_clicked()
{

    if (m_state.airportsColor == ui->btnAirportsColor->color()) {
        return;
    }
    m_state.airportsColor = ui->btnAirportsColor->color();
    if (ui->cbAirports->isChecked() == false) {
        return;
    }
    emit stateChanged();
}

void ControlPanel::on_btnHeliportsColor_clicked()
{
    if (m_state.heliportsColor == ui->btnHeliportsColor->color()) {
        return;
    }
    m_state.heliportsColor = ui->btnHeliportsColor->color();
    if (ui->cbHeliports->isChecked() == false) {
        return;
    }
    emit stateChanged();
}

void ControlPanel::on_btnCitiesColor_clicked()
{
    if (m_state.citiesColor == ui->btnCitiesColor->color()) {
        return;
    }
    m_state.citiesColor = ui->btnCitiesColor->color();
    if (ui->cbCities->isChecked() == false) {
        return;
    }
    emit stateChanged();
}

void ControlPanel::on_btnFinancingColor_clicked()
{
    if (m_state.financingColor == ui->btnFinancingColor->color()) {
        return;
    }
    m_state.financingColor = ui->btnFinancingColor->color();
    if (ui->cbFinancing->isChecked() == false) {
        return;
    }
    emit stateChanged();
}

void ControlPanel::on_btnTrafficColor_clicked()
{
    if (m_state.trafficColor == ui->btnTrafficColor->color()) {
        return;
    }
    m_state.trafficColor = ui->btnTrafficColor->color();
    if (ui->cbTraffic->isChecked() == false) {
        return;
    }
    emit stateChanged();
}

void ControlPanel::on_cbInternational_toggled(bool checked)
{
    if (m_state.international == checked) {
        return;
    }
    m_state.international = checked;
    emit stateChanged();
}

void ControlPanel::on_cbDomestic_toggled(bool checked)
{
    if (m_state.domestic == checked) {
        return;
    }
    m_state.domestic = checked;
    emit stateChanged();
}

void ControlPanel::on_cbRunwayCoverHard_toggled(bool checked)
{
    if (m_state.runwayCoverHard == checked) {
        return;
    }
    m_state.runwayCoverHard = checked;
    emit stateChanged();
}

void ControlPanel::on_cbRunwayCoverGround_toggled(bool checked)
{
    if (m_state.runwayCoverGround == checked) {
        return;
    }
    m_state.runwayCoverGround = checked;
    emit stateChanged();
}

void ControlPanel::on_cbRunwayType1_toggled(bool checked)
{
    if (m_state.runwayType1 == checked) {
        return;
    }
    m_state.runwayType1 = checked;
    emit stateChanged();
}

void ControlPanel::on_cbRunwayType2_toggled(bool checked)
{
    if (m_state.runwayType2 == checked) {
        return;
    }
    m_state.runwayType2 = checked;
    emit stateChanged();
}

void ControlPanel::on_cbRunwayType3_toggled(bool checked)
{
    if (m_state.runwayType3 == checked) {
        return;
    }
    m_state.runwayType3 = checked;
    emit stateChanged();
}

void ControlPanel::on_cbRunwayType4_toggled(bool checked)
{
    if (m_state.runwayType4 == checked) {
        return;
    }
    m_state.runwayType4 = checked;
    emit stateChanged();
}

void ControlPanel::on_cbRunwayType5_toggled(bool checked)
{
    if (m_state.runwayType5 == checked) {
        return;
    }
    m_state.runwayType5 = checked;
    emit stateChanged();
}

void ControlPanel::on_cbRunwayType6_toggled(bool checked)
{
    if (m_state.runwayType6 == checked) {
        return;
    }
    m_state.runwayType6 = checked;
    emit stateChanged();
}

void ControlPanel::on_cbRunwayNo_toggled(bool checked)
{
    if (m_state.runwayNo == checked) {
        return;
    }
    m_state.runwayNo = checked;
    emit stateChanged();
}

void ControlPanel::on_cbLightingConst_toggled(bool checked)
{
    if (m_state.lightingConst == checked) {
        return;
    }
    m_state.lightingConst = checked;
    emit stateChanged();
}

void ControlPanel::on_cbLightingOnRequest_toggled(bool checked)
{
    if (m_state.lightingOnRequest == checked) {
        return;
    }
    m_state.lightingOnRequest = checked;
    emit stateChanged();
}

void ControlPanel::on_cbLightingNo_toggled(bool checked)
{
    if (m_state.lightingNo == checked) {
        return;
    }
    m_state.lightingNo = checked;
    emit stateChanged();
}

void ControlPanel::on_cbOnlyFor_toggled(bool checked)
{
    if (m_state.onlyFor == checked) {
        return;
    }
    m_state.onlyFor = checked;

    m_state.regionList.clear();
    traverseTreeWidget<ControlPanel *, CustomCheckBox>(ui->treeRegions, this);
    m_state.regionList.removeDuplicates();

    emit stateChanged();
}

void ControlPanel::process(QTreeWidget *tree_widget, QTreeWidgetItem *tree_item)
{
    CustomCheckBox *checkbox = static_cast<CustomCheckBox *>(ui->treeRegions->itemWidget(tree_item, 0));
    m_state.regionList.append((checkbox->text()));

    (void) tree_widget;
}
