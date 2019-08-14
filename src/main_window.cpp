#include "main_window.h"

#include <QColor>
#include <QHBoxLayout>
#include <QMetaObject>
#include <QScreen>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_mapScene(new QQuickWidget(QUrl(QStringLiteral("qrc:/src/map.qml"))))
    , m_controlPanel(new ControlPanel)
{
    m_database = QSqlDatabase::addDatabase("QPSQL");
    m_database.setHostName("127.0.0.1");
    m_database.setDatabaseName("Test");
    m_database.setUserName("postgres");
    m_database.setPassword("privet1992");
    m_database.open();

    loadFonts();
    initControls();
    initLayouts();

    QRect screenRect = QGuiApplication::primaryScreen()->availableGeometry();
    int   dx         = 20;
    int   dy         = 50;
    setGeometry(screenRect.x() + dx, screenRect.y() + dy, screenRect.width() - 2 * dx, screenRect.height() - 2 * dy);
    this->showMaximized();

    connect(m_controlPanel, SIGNAL(stateChanged()), this, SLOT(test()));
    // для теста, потом удалить:
    emit m_controlPanel->stateChanged();
}

MainWindow::~MainWindow()
{
    m_database.close();
}

void MainWindow::loadFonts()
{
    this->setFont(FontManager::instance().regular(GuiConfig::FONT_SIZE_NORMAL));
}

void MainWindow::initControls()
{
    m_mapScene->setResizeMode(QQuickWidget::SizeRootObjectToView);
    m_mapScene->setMinimumWidth(512);
    m_mapScene->setMinimumHeight(512);

    TwoLevelTreeItems data;
    data.topLevels = {"Центральный ФО", "Северо-Западный ФО", "Южный ФО",     "Северо-Кавказский ФО",
                      "Приволжский ФО", "Уральский ФО",       "Сибирский ФО", "Дальневосточный ФО"};
    data.childrens.resize(data.topLevels.count());
    for (int i = 0; i < data.topLevels.count(); i++) {
        QSqlQuery query;
        query.exec("SELECT name_area FROM tab_areas WHERE id_fed_area = " + QString::number(i + 1) +
                   " ORDER BY name_area");
        while (query.next()) {
            data.childrens[i].append(query.value(0).toString());
        }
    }
    m_controlPanel->setRegionsToTree(data);
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


void MainWindow::test()
{
    StateOfParameters state = m_controlPanel->state();
    QColor            c1    = state.airportsColor;
    QColor            c2    = c1;
    c2.setAlpha(255);

    QString airportsQuery = "";
    if (state.airports) {
        airportsQuery = "SELECT TAir.air_inter_code, TAir.name_ru, TAir.air_latitude, TAir.air_longitude \
                         FROM tab_airports AS TAir WHERE TAir.id_air_type = 1";
    }

    SqlQueryModel model;
    model.setRadius(5);
    model.setColor(c1);
    model.setBorderColor(c2);
    model.setQuery(airportsQuery, m_database);
    m_mapScene->rootContext()->setContextProperty("airport_model", &model);
}
