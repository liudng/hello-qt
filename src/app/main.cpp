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

    // Load translations based on system locale
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    qDebug() << "UI Languages:" << uiLanguages;
    if (translator.load(QLocale::system(), "hello", "_", ":/i18n")) {
        qDebug() << "Translation loaded successfully";
        app.installTranslator(&translator);
    } else {
        qDebug() << "Failed to load translation";
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
