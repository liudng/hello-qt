// SPDX-FileCopyrightText: 2026 Liu Dong <liudng@hotmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later OR LGPL-3.0-or-later

#include <QApplication>
#include <QIcon>
#include <QDir>
#include <QLockFile>
#include <QStandardPaths>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QTranslator>
#include <QLocale>
#include <QSettings>
#include <QDebug>

#include "config.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // Create a lock file in the system's temporary directory to ensure only one
    // instance of the application runs at a time
    QString lockFilePath = QStandardPaths::writableLocation(QStandardPaths::TempLocation)
            + QDir::separator() + "hello.lock";
    QLockFile lockFile(lockFilePath);
    if (!lockFile.tryLock()) {
        qWarning("Another instance of the application is already running.");
        return 1;
    }

    // Set application metadata
    QApplication::setApplicationName("hello");
    QApplication::setApplicationDisplayName("Hello Qt");
    QApplication::setApplicationVersion(HELLO_VERSION);
    QApplication::setOrganizationDomain("io.github.liudng.hello");
    QApplication::setDesktopFileName("io.github.liudng.hello");
    QApplication::setStyle("fusion");
    QIcon::setThemeName("gnome");

    // Create the QApplication object
    QApplication app(argc, argv);

    // Load translations based on saved preference or system locale
    QTranslator translator;
    QSettings settings;
    QString savedLang = settings.value("appearance/language", "").toString();
    bool translatorLoaded = false;
    
    if (!savedLang.isEmpty()) {
        // Use saved language preference
        qDebug() << "Using saved language:" << savedLang;
        if (translator.load(QLocale(savedLang), "hello", "_", ":/i18n")) {
            qDebug() << "Translation loaded successfully from saved preference";
            app.installTranslator(&translator);
            translatorLoaded = true;
        } else {
            qDebug() << "Failed to load translation for saved language, falling back to system locale";
        }
    }
    
    // If no saved language or saved language failed, try system locale
    if (!translatorLoaded) {
        const QStringList uiLanguages = QLocale::system().uiLanguages();
        qDebug() << "UI Languages:" << uiLanguages;
        if (translator.load(QLocale::system(), "hello", "_", ":/i18n")) {
            qDebug() << "Translation loaded successfully from system locale";
            app.installTranslator(&translator);
        } else {
            qDebug() << "Failed to load translation";
        }
    }

    // Set up command line parser to handle options
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(app);

    // Create and show the main window
    hello::app::MainWindow mainWindow;
    mainWindow.show();

    // Start the event loop
    return app.exec();
}
