// SPDX-FileCopyrightText: 2026 Liu Dong <liudng@hotmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later OR LGPL-3.0-or-later

#pragma once

#include <QWidget>

namespace hello::app {

class AbstractPreferencePage
{
public:
    virtual ~AbstractPreferencePage() = default;
    virtual QString title() const = 0;
    virtual QWidget *widget() = 0;
    virtual void loadSettings() = 0;
    virtual void saveSettings() = 0;
};

}