#include "control_panel.h"
#include "gui_config.h"

#include <QSpacerItem>
#include <QVBoxLayout>


ControlPanel::ControlPanel(QWidget *parent)
    : QGroupBox(parent)
    , m_cbShowAirpots(new QCheckBox)
    , m_cbShowHeliports(new QCheckBox)
{
    initControls();
    initLayouts();

    this->setTitle(tr("Параметры"));
}

ControlPanel::~ControlPanel()
{
    delete m_cbShowAirpots;
    delete m_cbShowHeliports;
}

void ControlPanel::initControls()
{
    m_cbShowAirpots->setText(tr("Аэропорты"));
    m_cbShowAirpots->setChecked(true);

    m_cbShowHeliports->setText(tr("Вертодромы"));
    m_cbShowHeliports->setChecked(false);
}

void ControlPanel::initLayouts()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(GuiConfig::LAYOUT_MARGIN_SMALL);
    mainLayout->setSpacing(GuiConfig::LAYOUT_SPACING_SMALL);
    mainLayout->addWidget(m_cbShowAirpots);
    mainLayout->addWidget(m_cbShowHeliports);
    mainLayout->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
    this->setLayout(mainLayout);

    this->setMinimumWidth(150);
    this->setMaximumWidth(150);
}
