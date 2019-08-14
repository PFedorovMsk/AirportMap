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

    connect(m_controlPanel, SIGNAL(stateChanged()), this, SLOT(paintAirportsAndHeliports()));
    //connect(m_controlPanel, SIGNAL(stateChanged()), this, SLOT(paintCities()));

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

void MainWindow::paintAirportsAndHeliports()
{
    m_mapScene->rootContext()->setContextProperty("airport_model", nullptr);
    m_mapScene->rootContext()->setContextProperty("heliport_model", nullptr);

    StateOfParameters state = m_controlPanel->state();
    if ((!state.airports && !state.heliports) || (!state.international && !state.domestic) ||
        (!state.runwayCoverHard && !state.runwayCoverGround) ||
        (!state.runwayType1 && !state.runwayType2 && !state.runwayType3 && !state.runwayType4 && !state.runwayType5 &&
         !state.runwayType6 && !state.runwayNo)) {
        return;
    }

    bool needTabAreas  = state.onlyFor;
    bool needTabStrips = (!(state.runwayCoverHard && state.runwayCoverGround) ||
                          !(state.runwayType1 && state.runwayType2 && state.runwayType3 && state.runwayType4 &&
                            state.runwayType5 && state.runwayType6 && state.runwayNo));

    QString query = "";
    query += "SELECT TAir.name_ru, TAir.air_latitude, TAir.air_longitude FROM tab_airports AS TAir ";
    if (needTabAreas) {
        query += "INNER JOIN tab_areas AS TArea ON TAir.id_oktmo_area = TArea.id_oktmo_area ";
    }
    if (needTabStrips) {
        query += "INNER JOIN tab_strips AS TStrips ON TAir.id_air = TStrips.id_air ";
    }
    query += "WHERE ";

    if (state.onlyFor == true) {
        query += "(";
        for (int i = 0; i < state.regionList.count(); i++) {
            query += "TArea.name_area = '" + state.regionList.at(i) + "' ";
            if (i < state.regionList.count() - 1) {
                query += "OR ";
            }
        }
        query += ") AND";
    }

    if (state.international && !state.domestic) {
        query += " TAir.id_air_class = 1 AND";
    } else if (!state.international && state.domestic) {
        query += " TAir.id_air_class = 2 AND";
    }

    if (state.runwayCoverHard && !state.runwayCoverGround) {
        query += " TStrips.id_str_type = 1 AND";
    } else if (!state.runwayCoverHard && state.runwayCoverGround) {
        query += " TStrips.id_str_type = 2 AND";
    }

    if (needTabStrips) {
        QString subQuery = "";
        if (state.runwayType1) {
            subQuery += "TStrips.id_str_class = 1";
        }
        if (state.runwayType2) {
            if (subQuery.length() > 0) {
                subQuery += " OR ";
            }
            subQuery += "TStrips.id_str_class = 2";
        }
        if (state.runwayType3) {
            if (subQuery.length() > 0) {
                subQuery += " OR ";
            }
            subQuery += "TStrips.id_str_class = 3";
        }
        if (state.runwayType4) {
            if (subQuery.length() > 0) {
                subQuery += " OR ";
            }
            subQuery += "TStrips.id_str_class = 4";
        }
        if (state.runwayType5) {
            if (subQuery.length() > 0) {
                subQuery += " OR ";
            }
            subQuery += "TStrips.id_str_class = 5";
        }
        if (state.runwayType6) {
            if (subQuery.length() > 0) {
                subQuery += " OR ";
            }
            subQuery += "TStrips.id_str_class = 6";
        }
        if (state.runwayNo) {
            if (subQuery.length() > 0) {
                subQuery += " OR ";
            }
            subQuery += "TStrips.id_str_class = 7";
        }
        query += " (" + subQuery + ") AND";
    }

    if (state.airports) {
        QColor color       = state.airportsColor;
        QColor borderColor = color;
        borderColor.setAlpha(255);

        SqlQueryModel model;
        model.setRadius(4);
        model.setColor(color);
        model.setBorderColor(borderColor);
        model.setQuery(query + " TAir.id_air_type = 1", m_database);
        m_mapScene->rootContext()->setContextProperty("airport_model", &model);
    }

    if (state.heliports) {
        QColor color       = state.heliportsColor;
        QColor borderColor = color;
        borderColor.setAlpha(255);

        SqlQueryModel model;
        model.setRadius(4);
        model.setColor(color);
        model.setBorderColor(borderColor);
        model.setQuery(query + " TAir.id_air_type = 2", m_database);
        m_mapScene->rootContext()->setContextProperty("heliport_model", &model);
    }
}

void MainWindow::paintCities()
{
    qDebug() << "paintCIties start";
    m_mapScene->rootContext()->setContextProperty("cities_model", nullptr);

    StateOfParameters state = m_controlPanel->state();
    qDebug() << "state: " << state.cities;
    if (!(state.cities && state.onlyFor)) {
        qDebug() << "exit";
        return;
    }

    QString query = "";
    query += "SELECT TLC.name_city, TLC.latitude_city, TLC.longitude_city FROM tab_local_cities AS TLC ";
    query += "INNER JOIN tab_areas AS TArea ON TLC.id_oktmo_area = TArea.id_oktmo_area WHERE (";
    for (int i = 0; i < state.regionList.count(); i++) {
        query += "TArea.name_area = '" + state.regionList.at(i) + "' ";
        if (i < state.regionList.count() - 1) {
            query += "OR ";
        }
    }
    query += ")";

    qDebug() << "query = " << query;
    QColor color       = state.citiesColor;
    QColor borderColor = color;
    borderColor.setAlpha(255);

    SqlQueryModel model;
    model.setRadius(5);
    model.setColor(color);
    model.setBorderColor(borderColor);
    model.setQuery(query, m_database);
    m_mapScene->rootContext()->setContextProperty("cities_model", &model);
    qDebug() << "good finish";
}
