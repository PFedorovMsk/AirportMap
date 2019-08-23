#include "main_window.h"
#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString     locale = QLocale::system().name();
    QTranslator qtTranslator;
    if (qtTranslator.load("qt_" + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath))) {
        app.installTranslator(&qtTranslator);
    }

    MainWindow window;
    window.show();

    return app.exec();
}
