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
#include <QContextMenuEvent>

#include "mainwindow.h"
#include "preferencesdialog.h"
#include "centralwidget.h"

namespace hello::app {

MainWindow::MainWindow(QWidget *parent)
{
    QSettings settings;
    qDebug() << "Settings file path:" << settings.fileName();

    // Create the menu bar, toolbars, and status bar
    createMenuBar();

    // Create a central widget with a vertical layout and a button
    setCentralWidget(new CentralWidget(this));

    // Restore the geometry and state of the main window from QSettings
    bool restoredGeoMetry = restoreGeometry(settings.value("window/geometry").toByteArray());
    bool restoredState = restoreState(settings.value("window/state").toByteArray());
    // If the state could not be restored, set a default size for the main window
    if (!restoredGeoMetry || !restoredState) {
        int width = 800;
        int height = 600;
        resize(width, height);
    }

    // Show a "Ready" message in the status bar for 2 seconds
    statusBar()->showMessage(tr("Ready"), 2000);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings;

    // Save the geometry and state of the main window to QSettings before closing
    settings.setValue("window/geometry", saveGeometry());
    settings.setValue("window/state", saveState());
    settings.setValue("view/statusbar", statusBar()->isVisible());

    // Call the base class implementation to ensure proper closing behavior
    QMainWindow::closeEvent(event);
}

void MainWindow::createMenuBar()
{
    QSettings settings;

    // Create the File menu
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    // Create a toolbar for file operations
    QToolBar *fileToolBar = addToolBar(tr("File"));
    fileToolBar->setObjectName("FileToolBar");

    // Add "Exit" action to the File menu and toolbar
    QAction *exitAction = new QAction(QIcon::fromTheme("application-exit"), tr("Exit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);
    fileMenu->addAction(exitAction);
    fileToolBar->addAction(exitAction);

    // Create the Edit menu
    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    // Create a toolbar for edit operations
    QToolBar *editToolBar = addToolBar(tr("Edit"));
    editToolBar->setObjectName("EditToolBar");

    // Add "Perferences" action to the Edit menu and toolbar
    QAction *preferencesAction =
            new QAction(QIcon::fromTheme("preferences-system"), tr("Preferences"), this);
    preferencesAction->setShortcut(QKeySequence::Preferences);
    connect(preferencesAction, &QAction::triggered, this, [this]() {
        PreferencesDialog dialog(this);
        dialog.exec();
    });
    editMenu->addAction(preferencesAction);
    editToolBar->addAction(preferencesAction);

    // Create the View menu
    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));
    // Create a toolbar for view operations
    QToolBar *viewToolBar = addToolBar(tr("View"));
    viewToolBar->setObjectName("ViewToolBar");

    // Restore the visibility of the status bar from QSettings
    bool viewStatusbar = settings.value("view/statusbar", true).toBool();
    statusBar()->setVisible(viewStatusbar);

    // Add "Status Bar" action to the View menu and toolbar
    QAction *statusBarAction = new QAction(QIcon::fromTheme("info"), tr("Status Bar"), this);
    statusBarAction->setCheckable(true);
    statusBarAction->setChecked(viewStatusbar);
    connect(statusBarAction, &QAction::triggered, this,
            [this](bool checked) { statusBar()->setVisible(checked); });
    viewMenu->addAction(statusBarAction);
    viewToolBar->addAction(statusBarAction);

    // Create the Help menu
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    // Add "About" action to the Help menu
    QAction *aboutAction = helpMenu->addAction(tr("About"));
    aboutAction->setIcon(QIcon::fromTheme("help-about"));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::about()
{
    QMessageBox::about(this, "About",
                       "This is a simple Qt application demonstrating the use of QMainWindow, "
                       "QMenuBar, and QStatusBar.");
}

} // namespace hello::app