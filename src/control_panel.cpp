#include "control_panel.h"
#include "ui_control_panel.h"


ControlPanel::ControlPanel(QWidget *parent)
    : QGroupBox(parent)
    , ui(new Ui::ControlPanel)
{
    ui->setupUi(this);
}

ControlPanel::~ControlPanel()
{
    delete ui;
}
