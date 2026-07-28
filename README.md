# Hello

## Model/View

[Model/View Programming](https://doc.qt.io/qt-6.8/model-view-programming.html)

## Qt Widgets

[Qt Widgets](https://doc.qt.io/qt-6.8/qtwidgets-index.html)

### QLockFile

### QCommandLineParser

### QMainWindow

### i18n

### QAction

### QSettings

### QMenuBar

```c++
    // Create the File menu
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    // Add "Exit" action to the File menu
    QAction *exitAction = fileMenu->addAction(tr("Exit"));
    exitAction->setIcon(QIcon::fromTheme("application-exit"));
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);
```

```c++
    QSettings settings;
    // Create the View menu
    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));
    // Add "Show Status Bar" action to the View menu
    QAction *showStatusBarAction = viewMenu->addAction(tr("Show Status Bar"));
    showStatusBarAction->setCheckable(true);
    showStatusBarAction->setChecked(true);
    connect(showStatusBarAction, &QAction::triggered, this,
            [this](bool checked) { statusBar()->setVisible(checked); });
```


## CMake

[Getting started with CMake](https://doc.qt.io/qt-6.8/cmake-get-started.html)
[CMake Commands in Qt6 Core](https://doc.qt.io/qt-6.8/cmake-commands-qtcore.html)

## clang-format

[Qt Coding Style](https://wiki.qt.io/Qt_Coding_Style)
[clang-format Configuration](https://code.qt.io/cgit/qt/qt5.git/tree/_clang-format?h=6.8)

### vscode settings.json

```json
{
    "editor.formatOnSave": true,
    "C_Cpp.clang_format_style": "file"
}
```

## Clazy



## clang-tidy

```shell
clang-tidy -checks=* -header-filter=.* -p=. src/*.cpp -- -Iinclude
clang-tidy -checks=* -header-filter=.* -p=. src/*.cpp -- -Iinclude -Wno-unused-variable
```

## cppcheck

```shell
cppcheck --enable=all \
         --std=c++20 \
         --library=qt.cfg \
         --inconclusive \
         --suppress=missingIncludeSystem \
         --template="{file}:{line}:{severity}:{id}:{message}" \
         --quiet \
         --xml \
         -j 4 
         /path/to/your/source
```

## Sanitizer

AddressSanitizer (ASan)、LeakSanitizer (LSan) and UndefinedBehaviorSanitizer (UBSan).

```shell
clang++ -fsanitize=address,undefined -fno-omit-frame-pointer -g main.cpp
```

## SPDX

```
// SPDX-FileCopyrightText: 2026 Liu Dong <liudng@hotmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later OR LGPL-3.0-or-later
```