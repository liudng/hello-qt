# Hello

## Model/View

[Model/View Programming](https://doc.qt.io/qt-6.8/model-view-programming.html)

## CMake

[Getting started with CMake](https://doc.qt.io/qt-6.8/cmake-get-started.html)

## clang-format

```shell
clang-format -style=WebKit -dump-config > .clang-format
clang-format -i -style=WebKit src/*.cpp src/*.h
```

[Qt Coding Style](https://wiki.qt.io/Qt_Coding_Style)

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