#include "main_window.h"

#include <QColor>
#include <QHBoxLayout>
#include <QMetaObject>
#include <QScreen>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_graphWindow(new GraphWindow)
    , m_mapScene(new QQuickWidget(QUrl(QStringLiteral("qrc:/src/map.qml"))))
    , m_controlPanel(new ControlPanel)
    , m_databaseEditorPanel(new DatabaseEditorPanel)
    , m_sqlTableModel(nullptr)
    , m_databaseView(new QTableView)
    , m_databaseHostName("127.0.0.1")
    , m_databaseDatabaseName("Test2")
    , m_databaseUserName("postgres")
    , m_databasePassword("privet1992")
{
    loadFonts();
    initDatabase();
    initMapScene();
    initControlPanel();
    initDatabaseEditor();
    initLayouts();
    initScreenRect();
    initGraphWindow();

    connect(m_controlPanel, SIGNAL(mainStateChanged()), this, SLOT(paintMainObjects()));
    connect(m_controlPanel, SIGNAL(additionalStateChanged()), m_graphWindow, SLOT(onClear()));
    connect(m_controlPanel, SIGNAL(additionalStateChanged()), this, SLOT(paintAdditionalObjects()));
    connect(m_controlPanel, SIGNAL(additionalStateChanged()), this, SLOT(paintGraphPopulation()));
    connect(m_controlPanel, SIGNAL(additionalStateChanged()), this, SLOT(paintGraph()));

    emit paintMainObjects();
}

MainWindow::~MainWindow()
{
    m_database.close();
    m_graphWindow->close();
    delete m_graphWindow;
}

void MainWindow::loadFonts()
{
    this->setFont(FontManager::instance().regular(GuiConfig::FONT_SIZE_NORMAL));
}

void MainWindow::initDatabase()
{
    m_database = QSqlDatabase::addDatabase("QPSQL");

    m_database.setHostName(m_databaseHostName);
    m_database.setDatabaseName(m_databaseDatabaseName);
    m_database.setUserName(m_databaseUserName);
    m_database.setPassword(m_databasePassword);

    if (!m_database.open()) {
        QFile file(QCoreApplication::applicationDirPath() + "/AirportMap.ini");
        if (file.open(QFile::ReadOnly)) {
            QByteArray hostName         = file.readLine();
            QByteArray databaseName     = file.readLine();
            QByteArray userName         = file.readLine();
            QByteArray databasePassword = file.readLine();

            // последние 2 символа - \r\n - добавляются при переносе строки, удаляю:
            hostName.resize(hostName.size() - 2);
            databaseName.resize(databaseName.size() - 2);
            userName.resize(userName.size() - 2);

            m_database.setHostName(QString::fromStdString(hostName.toStdString()));
            m_database.setDatabaseName(QString::fromStdString(databaseName.toStdString()));
            m_database.setUserName(QString::fromStdString(userName.toStdString()));
            m_database.setPassword(QString::fromStdString(databasePassword.toStdString()));
        }
        file.close();

        if (!m_database.open()) {
            QMessageBox msgBox;
            msgBox.setText(tr("Ошибка!"));
            msgBox.setInformativeText(tr("Не удалось подключиться к базе данных"));
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setDefaultButton(QMessageBox::Ok);
            int res = msgBox.exec();
            if (res == QMessageBox::Ok) {
                QApplication::exit();
            }
        }
    }
}

void MainWindow::initMapScene()
{
    m_mapScene->rootContext()->setContextProperty("cities_model", nullptr);
    m_mapScene->rootContext()->setContextProperty("financing_model", nullptr);
    m_mapScene->rootContext()->setContextProperty("airport_model", nullptr);
    m_mapScene->rootContext()->setContextProperty("heliport_model", nullptr);
    m_mapScene->rootContext()->setContextProperty("cities_model", nullptr);
    m_mapScene->rootContext()->setContextProperty("stops_model", nullptr);
    m_mapScene->rootContext()->setContextProperty("ports_model", nullptr);
    m_mapScene->rootContext()->setContextProperty("train_stations_model", nullptr);

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
    m_controlPanel->setMinimumWidth(m_controlPanel->sizeHint().width());
}

void MainWindow::initDatabaseEditor()
{
    QSqlQuery sqlQuery("", m_database);
    sqlQuery.exec(QueryMaker::instance().selectDatabaseTableNames());
    QStringList list;
    while (sqlQuery.next()) {
        list.append(sqlQuery.value(0).toString());
    }

    m_databaseEditorPanel->setTablesList(list);
    m_databaseEditorPanel->setMinimumWidth(m_databaseEditorPanel->sizeHint().width());

    m_sqlTableModel = new QSqlTableModel(nullptr, m_database);
    m_sqlTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_sqlTableModel->setTable(list.first());
    m_sqlTableModel->select();
    m_databaseView->setModel(m_sqlTableModel);

    m_databaseView->setAlternatingRowColors(true);
    m_databaseView->setSortingEnabled(true);
    m_databaseView->horizontalHeader()->setVisible(true);

    connect(m_databaseEditorPanel, SIGNAL(save()), m_sqlTableModel, SLOT(submitAll()));
    connect(m_databaseEditorPanel, SIGNAL(undo()), m_sqlTableModel, SLOT(revertAll()));
    connect(m_databaseEditorPanel, SIGNAL(insert()), this, SLOT(insertRow()));
    connect(m_databaseEditorPanel, SIGNAL(remove()), this, SLOT(removeRow()));
    connect(m_databaseEditorPanel, SIGNAL(tableListChanged(QString)), this, SLOT(changeTable(QString)));
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
    tab2Layout->addWidget(m_databaseView);
    tab2Layout->addWidget(m_databaseEditorPanel);
    tab2Widget->setLayout(tab2Layout);

    // main:

    QTabWidget *mainWidget = new QTabWidget;
    mainWidget->addTab(tab1Widget, tr("Карта"));
    mainWidget->addTab(tab2Widget, tr("Редактор БД"));

    setCentralWidget(mainWidget);


    int minPanelWidth = m_controlPanel->minimumWidth();
    if (int width = m_databaseEditorPanel->minimumWidth() > minPanelWidth) {
        minPanelWidth = width;
    }
    m_controlPanel->setMinimumWidth(minPanelWidth);
    m_databaseEditorPanel->setMinimumWidth(minPanelWidth);

    centralWidget()->setMinimumWidth(3 * GuiConfig::LAYOUT_MARGIN_BIG + m_mapScene->minimumWidth() + minPanelWidth);
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

void MainWindow::initGraphWindow()
{
    m_graphWindow->setWindowTitle(tr("Графики"));
    m_graphWindow->setMinimumWidth(640);
    m_graphWindow->setMinimumHeight(480);

    connect(this, SIGNAL(clear()), m_graphWindow, SLOT(onClear()));

    m_graphWindow->setSheetCount(1);
    m_graphWindow->updatePlotter();
    m_graphWindow->hide();
}

void MainWindow::insertRow()
{
    m_sqlTableModel->insertRow(m_sqlTableModel->rowCount());
}

void MainWindow::removeRow()
{
    int selectedRow = m_databaseView->currentIndex().row();
    if (selectedRow >= 0 && selectedRow < m_sqlTableModel->rowCount()) {
        m_sqlTableModel->removeRow(selectedRow);
    }
}

void MainWindow::changeTable(const QString &tableName)
{
    m_sqlTableModel->setTable(tableName);
    m_sqlTableModel->select();
    m_databaseView->setModel(m_sqlTableModel);
}

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

    if (state.financing) {
        QColor        color       = state.financingColor;
        QColor        borderColor = colorWithoutAlpha(color);
        SqlQueryModel model;
        model.setMaxParamValue(25000); // TODO взять из БД максимальное значение
        model.setRadius(50);
        model.setColor(color);
        model.setBorderColor(borderColor);
        model.setQuery(QueryMaker::instance().selectFinancing(state), m_database);
        m_mapScene->rootContext()->setContextProperty("financing_model", &model);
    }

    if (state.airports) {
        QColor        color       = state.airportsColor;
        QColor        borderColor = colorWithoutAlpha(color);
        SqlQueryModel model;
        model.setRadius(5);
        model.setColor(color);
        model.setBorderColor(borderColor);
        model.setQuery(QueryMaker::instance().selectAirports(state), m_database);
        m_mapScene->rootContext()->setContextProperty("airport_model", &model);
    }

    if (state.heliports) {
        QColor        color       = state.heliportsColor;
        QColor        borderColor = colorWithoutAlpha(color);
        SqlQueryModel model;
        model.setRadius(5);
        model.setColor(color);
        model.setBorderColor(borderColor);
        model.setQuery(QueryMaker::instance().selectHeliports(state), m_database);
        m_mapScene->rootContext()->setContextProperty("heliport_model", &model);
    }
}

void MainWindow::paintAdditionalObjects()
{
    m_mapScene->rootContext()->setContextProperty("cities_model", nullptr);
    m_mapScene->rootContext()->setContextProperty("stops_model", nullptr);
    m_mapScene->rootContext()->setContextProperty("ports_model", nullptr);
    m_mapScene->rootContext()->setContextProperty("train_stations_model", nullptr);

    StateOfParameters state = m_controlPanel->state();

    if (state.regionList.count() == 0) {
        return;
    }

    if (state.cities) {
        QColor        color       = state.citiesColor1;
        QColor        borderColor = colorWithoutAlpha(color);
        SqlQueryModel model;
        model.setRadius(4);
        model.setColor(color);
        model.setAdditionalColor(color); // TODO set color2 != color1
        model.setBorderColor(borderColor);
        model.setQuery(QueryMaker::instance().selectCities(state), m_database);
        m_mapScene->rootContext()->setContextProperty("cities_model", &model);
    }

    if (state.stops) {
        QColor        color       = state.stopsColor;
        QColor        borderColor = colorWithoutAlpha(color);
        SqlQueryModel model;
        model.setRadius(4);
        model.setColor(color);
        model.setBorderColor(borderColor);
        model.setQuery(QueryMaker::instance().selectStops(state), m_database);
        m_mapScene->rootContext()->setContextProperty("stops_model", &model);
    }

    if (state.ports) {
        QColor        color       = state.portsColor;
        QColor        borderColor = colorWithoutAlpha(color);
        SqlQueryModel model;
        model.setRadius(4);
        model.setColor(color);
        model.setBorderColor(borderColor);
        model.setQuery(QueryMaker::instance().selectPorts(state), m_database);
        m_mapScene->rootContext()->setContextProperty("ports_model", &model);
    }

    if (state.trainStations) {
        QColor        color       = state.trainStationsColor;
        QColor        borderColor = colorWithoutAlpha(color);
        SqlQueryModel model;
        model.setRadius(4);
        model.setColor(color);
        model.setBorderColor(borderColor);
        model.setQuery(QueryMaker::instance().selectTrainStations(state), m_database);
        m_mapScene->rootContext()->setContextProperty("train_stations_model", &model);
    }
}

void MainWindow::makeGraphData(const QVector<double> &xData, const QVector<double> &yData,
                               QVector<QVector<double>> &xResult, QVector<QVector<double>> &yResult)
{
    QVector<double> intervals;
    QVector<double> values;

    double step  = xData.last() / 10;
    long   lStep = long(step);
    while (lStep % 5000 != 0) {
        lStep++;
    }
    step        = double(lStep);
    double xMax = step * 10;

    for (double x = 0.0; x < xMax + step; x += step) {
        intervals.append(x);
    }

    values.resize(intervals.count());
    int index = 0;

    for (int i = 0; i < intervals.count() - 1; i++) {
        double value = 0;
        for (int j = index; j < xData.count(); j++) {
            if (xData[j] < intervals[i + 1]) {
                value += yData[j];
            } else {
                index = j;
                break;
            }
        }
        values[i + 1] = value;
    }

    if (intervals.count() % 2 != 0) {
        intervals.append(intervals.last() + step);
        values.append(values.last());
    }

    QVector<double> x(4), y(4);
    for (int i = 0; i < intervals.count() - 1; i++) {
        x[0] = intervals[i];
        x[1] = intervals[i];
        x[2] = intervals[i + 1];
        x[3] = intervals[i + 1];

        y[0] = 0;
        y[1] = values[i + 1];
        y[2] = values[i + 1];
        y[3] = 0;

        xResult.append(x);
        yResult.append(y);
    }
}

void MainWindow::paintGraphPopulation()
{
    StateOfParameters state = m_controlPanel->state();
    if (state.regionList.count() == 0) {
        return;
    }

    QSqlQuery       sqlQuery("", m_database);
    QVector<double> taxAvg, population;

    sqlQuery.exec(QueryMaker::instance().selectPopulationAndTax(state));
    while (sqlQuery.next()) {
        double val0 = sqlQuery.value(0).toDouble();
        double val1 = sqlQuery.value(1).toDouble();
        if (std::isnan(val0) || std::isnan(val1) || std::isinf(val0) || std::isinf(val1)) {
            continue;
        }
        taxAvg.append(val0);
        population.append(val1 / 1000000.0);
    }

    if (taxAvg.count() < 3 || population.count() < 3) {
        return;
    }
    taxAvg.removeLast();
    population.removeLast();

    QVector<QVector<double>> x, y;
    makeGraphData(taxAvg, population, x, y);

    QPen pen1(Qt::red);
    pen1.setWidthF(2.0);
    QPen pen2(Qt::darkRed);
    pen2.setWidthF(2.0);

    if (m_graphWindow->sheetCount() < 2) {
        m_graphWindow->setSheetCount(2);
    }
    m_graphWindow->sheet(0).setTitleLabel(tr("Графики"));
    m_graphWindow->sheet(0).setSubTitleLabel(tr("количество людей с данными средними доходами"));
    for (int i = 0; i < x.count(); i++) {
        QString name = "[" + QString::number(x[i].first()) + ", " + QString::number(x[i].last()) + ")";
        m_graphWindow->sheet(0).addCurve(x[i], y[i], name, i % 2 == 0 ? pen1 : pen2);
    }
    m_graphWindow->sheet(0).setXLabel(tr("средние доходы, руб."));
    m_graphWindow->updatePlotter();
    m_graphWindow->show();
}

void MainWindow::paintGraph()
{
    StateOfParameters state = m_controlPanel->state();
    if (state.regionList.count() == 0) {
        return;
    }

    QSqlQuery       sqlQuery("", m_database);
    QVector<double> taxAvg, citiesCount;

    sqlQuery.exec(QueryMaker::instance().selectCitiesAndTax(state));
    while (sqlQuery.next()) {
        double val0 = sqlQuery.value(0).toDouble();
        double val1 = sqlQuery.value(1).toDouble();
        if (std::isnan(val0) || std::isnan(val1) || std::isinf(val0) || std::isinf(val1)) {
            continue;
        }
        taxAvg.append(val0);
        citiesCount.append(val1);
    }

    if (taxAvg.count() < 3 || citiesCount.count() < 3) {
        return;
    }
    taxAvg.removeLast();
    citiesCount.removeLast();

    QVector<QVector<double>> x, y;
    makeGraphData(taxAvg, citiesCount, x, y);

    QPen pen1(Qt::blue);
    pen1.setWidthF(2.0);
    QPen pen2(Qt::darkBlue);
    pen2.setWidthF(2.0);

    if (m_graphWindow->sheetCount() < 2) {
        m_graphWindow->setSheetCount(2);
    }
    m_graphWindow->sheet(1).setTitleLabel(tr("График"));
    m_graphWindow->sheet(1).setSubTitleLabel(tr("количество населенных пунктов с данными средними доходами"));
    m_graphWindow->sheet(1).setXLabel(tr("средние доходы, руб."));
    for (int i = 0; i < x.count(); i++) {
        QString name = "[" + QString::number(x[i].first()) + ", " + QString::number(x[i].last()) + ")";
        m_graphWindow->sheet(1).addCurve(x[i], y[i], name, i % 2 == 0 ? pen1 : pen2);
    }
    m_graphWindow->updatePlotter();
    m_graphWindow->show();
}
