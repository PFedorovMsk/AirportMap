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
    , m_databaseHostName("127.0.0.1")
    , m_databaseDatabaseName("Test")
    , m_databaseUserName("postgres")
    , m_databasePassword("privet1992")
{
    initDatabase();
    loadFonts();
    initMapScene();
    initControlPanel();
    initLayouts();
    initScreenRect();

    connect(m_controlPanel, SIGNAL(mainStateChanged()), this, SLOT(paintMainObjects()));
    connect(m_controlPanel, SIGNAL(additionalStateChanged()), this, SLOT(paintAdditionalObjects()));

    emit paintMainObjects();
}

MainWindow::~MainWindow()
{
    m_database.close();
}

void MainWindow::initDatabase()
{
    m_database = QSqlDatabase::addDatabase("QPSQL");

    m_database.setHostName("127.0.0.1");
    m_database.setDatabaseName("Test");
    m_database.setUserName("postgres");
    m_database.setPassword("privet1992");

    if (m_database.open()) {
        return;
    }
}

void MainWindow::loadFonts()
{
    this->setFont(FontManager::instance().regular(GuiConfig::FONT_SIZE_NORMAL));
}

void MainWindow::initMapScene()
{
    m_mapScene->rootContext()->setContextProperty("cities_model", nullptr);
    m_mapScene->rootContext()->setContextProperty("financing_model", nullptr);
    m_mapScene->rootContext()->setContextProperty("airport_model", nullptr);
    m_mapScene->rootContext()->setContextProperty("heliport_model", nullptr);

    m_mapScene->setResizeMode(QQuickWidget::SizeRootObjectToView);
    m_mapScene->setMinimumWidth(512);
    m_mapScene->setMinimumHeight(512);
}

void MainWindow::initControlPanel()
{
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

void MainWindow::initScreenRect()
{
    QRect screenRect = QGuiApplication::primaryScreen()->availableGeometry();
    int   dx         = 20;
    int   dy         = 50;
    setGeometry(screenRect.x() + dx, screenRect.y() + dy, screenRect.width() - 2 * dx, screenRect.height() - 2 * dy);
    this->showMaximized();
}

// slots:

inline QColor colorWithoutAlpha(const QColor &color)
{
    QColor res = color;
    res.setAlpha(255);
    return res;
}

void MainWindow::paintMainObjects()
{
    m_mapScene->rootContext()->setContextProperty("financing_model", nullptr);
    m_mapScene->rootContext()->setContextProperty("airport_model", nullptr);
    m_mapScene->rootContext()->setContextProperty("heliport_model", nullptr);

    StateOfParameters state = m_controlPanel->state();

    QString financingQuery = "";
    QString airportsQuery  = "";
    QString heliportsQuery = "";

    makeFinancingQuery(state, financingQuery);
    makeAirpotsAndHeliportsQuery(state, airportsQuery, heliportsQuery);

    if (financingQuery.length() > 0) {
        QColor        color       = state.financingColor;
        QColor        borderColor = colorWithoutAlpha(color);
        SqlQueryModel model;
        model.setRadius(50);
        model.setColor(color);
        model.setBorderColor(borderColor);
        model.setQuery(financingQuery, m_database);
        m_mapScene->rootContext()->setContextProperty("financing_model", &model);
    }

    if (airportsQuery.length() > 0) {
        QColor        color       = state.airportsColor;
        QColor        borderColor = colorWithoutAlpha(color);
        SqlQueryModel model;
        model.setRadius(5);
        model.setColor(color);
        model.setBorderColor(borderColor);
        model.setQuery(airportsQuery, m_database);
        m_mapScene->rootContext()->setContextProperty("airport_model", &model);
    }

    if (heliportsQuery.length() > 0) {
        QColor        color       = state.heliportsColor;
        QColor        borderColor = colorWithoutAlpha(color);
        SqlQueryModel model;
        model.setRadius(5);
        model.setColor(color);
        model.setBorderColor(borderColor);
        model.setQuery(heliportsQuery, m_database);
        m_mapScene->rootContext()->setContextProperty("heliport_model", &model);
    }
}

void MainWindow::paintAdditionalObjects()
{
    m_mapScene->rootContext()->setContextProperty("cities_model", nullptr);

    QString           citiesQuery = "";
    StateOfParameters state       = m_controlPanel->state();

    makeCitiesQuery(state, citiesQuery);

    if (citiesQuery.length() > 0) {
        QColor        color       = state.citiesColor;
        QColor        borderColor = colorWithoutAlpha(color);
        SqlQueryModel model;
        model.setRadius(4);
        model.setColor(color);
        model.setBorderColor(borderColor);
        model.setQuery(citiesQuery, m_database);
        m_mapScene->rootContext()->setContextProperty("cities_model", &model);
    }
}

void MainWindow::makeCitiesQuery(const StateOfParameters &state, QString &citiesQuery)
{
    citiesQuery = "";

    if (!state.cities) {
        return;
    }

    citiesQuery += "SELECT TLC.name_city, TLC.latitude_city, TLC.longitude_city ";
    citiesQuery += "FROM tab_local_cities AS TLC ";

    if (state.onlyFor && state.regionList.count() > 0) {
        citiesQuery += "INNER JOIN tab_municipal_areas AS TMA ON TLC.id_oktmo_municip = TMA.id_oktmo_municip ";
        citiesQuery += "INNER JOIN tab_areas AS TA ON TMA.id_oktmo_area = TA.id_oktmo_area ";
        citiesQuery += "INNER JOIN tab_federal_areas AS TFA ON TA.id_fed_area = TFA.id_fed_area WHERE (";
        for (int i = 0; i < state.regionList.count(); i++) {
            citiesQuery += "TA.name_area = '" + state.regionList.at(i) + "' ";
            if (i < state.regionList.count() - 1) {
                citiesQuery += "OR ";
            }
        }
        citiesQuery += ")";
    }
}

void MainWindow::makeFinancingQuery(const StateOfParameters &state, QString &financingQuery)
{
    financingQuery = "";

    if (!state.financing) {
        return;
    }

    financingQuery += "SELECT TA.name_ru, TA.air_latitude, TA.air_longitude, TE.budget_mil_rub::numeric, ";
    financingQuery += "TE.extrabudget_mil_rub::numeric, SUM(budget_mil_rub + extrabudget_mil_rub)::numeric AS summa ";
    financingQuery += "FROM tab_airports AS TA INNER JOIN tab_economic as TE ON TA.id_air = TE.id_air ";
    if (state.budget) {
        financingQuery += "WHERE TE.extrabudget_mil_rub::numeric <= 0 ";
    }
    financingQuery +=
        "GROUP BY TA.name_ru, TA.air_latitude, TA.air_longitude, TE.budget_mil_rub, TE.extrabudget_mil_rub ";
}

void MainWindow::makeAirpotsAndHeliportsQuery(const StateOfParameters &state, QString &airportsQuery,
                                              QString &heliportsQuery)
{
    airportsQuery  = "";
    heliportsQuery = "";

    if (!state.airports && !state.heliports) {
        return;
    }

    bool needTabStrips = (!(state.runwayCoverHard && state.runwayCoverGround) ||
                          !(state.runwayType1 && state.runwayType2 && state.runwayType3 && state.runwayType4 &&
                            state.runwayType5 && state.runwayType6 && state.runwayNo));

    QString query = "SELECT TAir.name_ru, TAir.air_latitude, TAir.air_longitude FROM tab_airports AS TAir ";
    if (needTabStrips) {
        query += "INNER JOIN tab_strips AS TStrips ON TAir.id_air = TStrips.id_air ";
    }
    query += "WHERE ";

    if (state.international && !state.domestic) {
        query += " TAir.id_air_class = 1 AND ";
    } else if (!state.international && state.domestic) {
        query += " TAir.id_air_class = 2 AND ";
    }

    if (state.runwayCoverHard && !state.runwayCoverGround) {
        query += " TStrips.id_str_type = 1 AND ";
    } else if (!state.runwayCoverHard && state.runwayCoverGround) {
        query += " TStrips.id_str_type = 2 AND ";
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
        query += " (" + subQuery + ") AND ";
    }

    if (state.airports) {
        airportsQuery = query + "TAir.id_air_type = 1";
    }
    if (state.heliports) {
        heliportsQuery = query + "TAir.id_air_type = 2";
    }
}
