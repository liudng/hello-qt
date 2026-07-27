// SPDX-FileCopyrightText: 2026 Liu Dong <liudng@hotmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later OR LGPL-3.0-or-later

#include <QSettings>
#include <QScreen>
#include <QApplication>
#include <QCursor>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QKeySequence>
#include <QMessageBox>
#include <QToolBar>
#include <QIcon>
#include <QStatusBar>
#include <QLabel>
#include <QProgressBar>

#include "mainwindow.h"

namespace hello::app {

MainWindow::MainWindow(QWidget *parent)
{
    QSettings settings;
    qDebug() << "Settings file path:" << settings.fileName();

    // Create the menu bar, toolbars, and status bar
    createMenuBar();
    createToolBars();
    createStatusBar();

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

void MainWindow::createMenuBar()
{
    // Create the File menu
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    // Add "Exit" action to the File menu
    QAction *exitAction = fileMenu->addAction(tr("Exit"));
    exitAction->setIcon(QIcon::fromTheme("application-exit"));
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    // Create the Help menu
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    // Add "About" action to the Help menu
    QAction *aboutAction = helpMenu->addAction(tr("About"));
    aboutAction->setIcon(QIcon::fromTheme("help-about"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createToolBars()
{
    // Create a toolbar for file operations
    QToolBar *fileToolBar = addToolBar(tr("File"));
    // Add "Exit" action to the toolbar
    QAction *exitAction = fileToolBar->addAction(tr("Exit"));
    exitAction->setIcon(QIcon::fromTheme("application-exit"));
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    // Create a toolbar for help operations
    QToolBar *helpToolBar = addToolBar(tr("Help"));
    // Add "About" action to the toolbar
    QAction *aboutAction = helpToolBar->addAction(tr("About"));
    aboutAction->setIcon(QIcon::fromTheme("help-about"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"), 2000);
}

void MainWindow::about()
{
    QMessageBox::about(this, "About",
                       "This is a simple Qt application demonstrating the use of QMainWindow, "
                       "QMenuBar, and QStatusBar.");
}

void MainWindow::updateStatusBar() { }

} // namespace hello::app