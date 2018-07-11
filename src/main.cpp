#include "mainwindow.h"

#include <QApplication>
#include <QFileInfo>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString appName = QCoreApplication::applicationName().toLower();
    QString locale = QLocale::system().name();
    QString translationsPath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    QString appDirectory = app.applicationDirPath();

#if defined(Q_OS_MAC)
    QFileInfo scTranslationsPath(appDirectory + "/../../../data/");
#elif defined(Q_OS_UNIX)
    QFileInfo scTranslationsPath(appDirectory + "/../share/net.bartkessels." + appName + "/translations/");
#else
    QFileInfo scTranslationsPath(appDirectory + "/data/");
#endif

    /* Load Qt translations */
    QTranslator qtTranslator;
    bool qtTranslationFound = qtTranslator.load("qt_" + locale,
                                                translationsPath);

    if (qtTranslationFound) {
        app.installTranslator(&qtTranslator);
    }

    /* Load SimpleConvert translations */
    QTranslator scTranslator;
    bool scTranslationsFound = scTranslator.load(appName + "_" + locale,
                                                 scTranslationsPath.absolutePath());

    if (scTranslationsFound) {
        app.installTranslator(&scTranslator);
    }

    /* Display main window */
    MainWindow w;
    w.show();

    return app.exec();
}
