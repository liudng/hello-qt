// SPDX-FileCopyrightText: 2026 Liu Dong <liudng@hotmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later OR LGPL-3.0-or-later

#include "mainwindow.h"

namespace hello::texteditor {

MainWindow::MainWindow(QWidget *parent) { }

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

void MainWindow::closeEvent(QCloseEvent *event) { }

}