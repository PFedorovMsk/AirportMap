#include "main_window.h"

#include <QHBoxLayout>
#include <QScreen>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_mapScene(new QQuickWidget(QUrl(QStringLiteral("qrc:/src/map.qml"))))
    , m_controlPanel(new ControlPanel)
{
    loadFonts();
    initControls();
    initLayouts();

    QRect screenRect = QGuiApplication::primaryScreen()->availableGeometry();
    setGeometry(screenRect.x() + 25, screenRect.y() + 50, this->minimumWidth(), this->minimumHeight());
}

MainWindow::~MainWindow() {}

void MainWindow::loadFonts()
{
    this->setFont(FontManager::instance().regular(GuiConfig::FONT_SIZE_NORMAL));
}

void MainWindow::initControls()
{
    m_mapScene->setResizeMode(QQuickWidget::SizeRootObjectToView);
    m_mapScene->setMinimumWidth(512);
    m_mapScene->setMinimumHeight(512);
}

void MainWindow::initLayouts()
{
    // tab 1:

    QWidget *    tab1Widget = new QWidget;
    QHBoxLayout *tab1Layout = new QHBoxLayout;
    tab1Layout->setMargin(GuiConfig::LAYOUT_MARGIN_SMALL);
    tab1Layout->setSpacing(GuiConfig::LAYOUT_SPACING_SMALL);
    tab1Layout->addWidget(m_mapScene);
    tab1Layout->addWidget(m_controlPanel);
    tab1Widget->setLayout(tab1Layout);

    // tab 2:

    QWidget *    tab2Widget = new QWidget;
    QHBoxLayout *tab2Layout = new QHBoxLayout;
    tab2Layout->setMargin(GuiConfig::LAYOUT_MARGIN_SMALL);
    tab2Layout->setSpacing(GuiConfig::LAYOUT_SPACING_SMALL);
    tab2Widget->setLayout(tab2Layout);

    // main:

    QTabWidget *mainWidget = new QTabWidget;
    mainWidget->addTab(tab1Widget, tr("Карта"));
    mainWidget->addTab(tab2Widget, tr("Другое"));

    setCentralWidget(mainWidget);

    centralWidget()->setMinimumWidth(3 * GuiConfig::LAYOUT_MARGIN_BIG + m_mapScene->minimumWidth() +
                                     m_controlPanel->minimumWidth());
    setMinimumWidth(this->layout()->margin() * 2 + centralWidget()->minimumWidth());
}

// slots:

void MainWindow::onClear() {}
