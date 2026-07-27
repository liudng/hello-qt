// SPDX-FileCopyrightText: 2026 Liu Dong <liudng@hotmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later OR LGPL-3.0-or-later

#include <QApplication>
#include <QIcon>
#include <QDir>
#include <QLockFile>
#include <QStandardPaths>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "config.h"
#include "../texteditor/mainwindow.h"

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

    QApplication::setApplicationName("Hello Qt");
    QApplication::setApplicationVersion(HELLO_VERSION);
    QApplication::setDesktopFileName("io.github.liudng.hello");
    QApplication::setStyle("fusion");
    QIcon::setThemeName("gnome");

    // Create the QApplication object
    QApplication app(argc, argv);

    // Set up command line parser to handle options
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(app);

    hello::texteditor::MainWindow mainWindow;
    mainWindow.show();

    // Start the event loop
    return app.exec();
}
