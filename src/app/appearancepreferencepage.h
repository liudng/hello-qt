// SPDX-FileCopyrightText: 2026 Liu Dong <liudng@hotmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later OR LGPL-3.0-or-later

#pragma once

#include <QWidget>
#include <QComboBox>
#include <QTranslator>

#include "abstractpreferencepage.h"

namespace hello::app {

class AppearancePreferencePage : public QWidget, public AbstractPreferencePage
{
    Q_OBJECT
public:
    explicit AppearancePreferencePage(QWidget *parent = nullptr);
    QString title() const override;
    QWidget *widget() override;
    void loadSettings() override;
    void saveSettings() override;

private:
    QStringList getAvailableIconThemes() const;
    QStringList getAvailableLanguages() const;
    void applyLanguage(const QString &langCode);
    // 控件指针
    QComboBox *m_languageCombo;
    QComboBox *m_styleCombo;
    QComboBox *m_iconThemeCombo;
    QTranslator *m_translator = nullptr;
};

} // namespace hello::app