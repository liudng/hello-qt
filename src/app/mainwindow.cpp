// SPDX-FileCopyrightText: 2026 Liu Dong <liudng@hotmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later OR LGPL-3.0-or-later

#include <QSettings>
#include <QScreen>
#include <QApplication>
#include <QCursor>
#include "mainwindow.h"

namespace hello::app {

MainWindow::MainWindow(QWidget *parent)
{
    QSettings settings;
    qDebug() << "Settings file path:" << settings.fileName();

    // Restore the geometry and state of the main window from QSettings
    bool restoredGeoMetry = restoreGeometry(settings.value("window/geometry").toByteArray());
    bool restoredState = restoreState(settings.value("window/state").toByteArray());
    // If the state could not be restored, set a default size for the main window
    if (!restoredGeoMetry || !restoredState) {
        int width = 800;
        int height = 600;
        resize(width, height);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings;

    // Save the geometry and state of the main window to QSettings before closing
    settings.setValue("window/geometry", saveGeometry());
    settings.setValue("window/state", saveState());

    // Call the base class implementation to ensure proper closing behavior
    QMainWindow::closeEvent(event);
}

void MainWindow::createActions() { }

void MainWindow::createMenus() { }

void MainWindow::createToolBars() { }

void MainWindow::createStatusBar() { }

void MainWindow::readSettings() { }

void MainWindow::writeSettings() { }

bool MainWindow::maybeSave()
{
    return false;
}

void MainWindow::loadFile(const QString &fileName) { }

bool MainWindow::saveFile(const QString &fileName)
{
    return false;
}

void MainWindow::setCurrentFile(const QString &fileName) { }

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QString();
}

void MainWindow::newFile() { }

void MainWindow::open() { }

bool MainWindow::save()
{
    return false;
}

bool MainWindow::saveAs()
{
    return false;
}

void MainWindow::about() { }

void MainWindow::updateStatusBar() { }

} // namespace hello::app