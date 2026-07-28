// SPDX-FileCopyrightText: 2026 Liu Dong <liudng@hotmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later OR LGPL-3.0-or-later

#pragma once

#include <QDialog>
class QListWidget;
class QStackedWidget;
class QDialogButtonBox;

namespace hello::app {

class PreferencesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PreferencesDialog(QWidget *parent = nullptr);

private slots:
    void onCategoryChanged(int index);
    void onAccepted();
    void onApply();

private:
    void loadSettings();
    void saveSettings();
    void createCategories();

    QListWidget *m_categoryList;
    QStackedWidget *m_stackedWidget;
    QDialogButtonBox *m_buttonBox;
};

} // namespace hello::app