#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString locale = QLocale::system().name();
    QString translationsPath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);

    /* Load Qt translations */
    QTranslator qtTranslator;
    bool qtTranslationFound = qtTranslator.load("qt_" + locale,
                                                translationsPath);

    if (qtTranslationFound) {
        app.installTranslator(&qtTranslator);
    }

    /* Load Qt Base translations */
    QTranslator qtBaseTranslator;
    bool qtBaseTranslationsFound = qtBaseTranslator.load("qtbase_" + locale,
                                                         translationsPath);

    if (qtBaseTranslationsFound) {
        app.installTranslator(&qtBaseTranslator);
    }

    /* Load SimpleConvert translations */
    QTranslator scTranslator;
    bool scTranslationsFound = scTranslator.load("simpleconvert_" + locale,
                                                 translationsPath);

    if (scTranslationsFound) {
        app.installTranslator(&scTranslator);
    }

    /* Display main window */
    MainWindow w;
    w.show();

    return app.exec();
}
