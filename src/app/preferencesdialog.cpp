// SPDX-FileCopyrightText: 2026 Liu Dong <liudng@hotmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later OR LGPL-3.0-or-later

#include <QListWidget>
#include <QStackedWidget>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSettings>
#include <QPushButton>

#include "preferencesdialog.h"

namespace hello::app {

PreferencesDialog::PreferencesDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Preferences"));
    setModal(true);

    // 创建垂直布局，作为 this 的唯一布局
    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    // 创建水平布局（不设置父）
    QHBoxLayout *mainLayout = new QHBoxLayout();
    // 水平布局作为子布局
    outerLayout->addLayout(mainLayout);

    // 左侧分类列表
    m_categoryList = new QListWidget(this);
    m_categoryList->setFixedWidth(120);
    m_categoryList->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    connect(m_categoryList, &QListWidget::currentRowChanged, this,
            &PreferencesDialog::onCategoryChanged);
    mainLayout->addWidget(m_categoryList);

    // 右侧堆叠窗口
    m_stackedWidget = new QStackedWidget(this);
    mainLayout->addWidget(m_stackedWidget, 1); // 占用剩余空间

    // 底部按钮
    m_buttonBox = new QDialogButtonBox(
            QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Apply, this);
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, &PreferencesDialog::onAccepted);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(m_buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this,
            &PreferencesDialog::onApply);
    outerLayout->addWidget(m_buttonBox);

    // 创建分类和页面
    createCategories();
    m_categoryList->setCurrentRow(0);
    loadSettings();
}

void PreferencesDialog::createCategories()
{
    // 添加分类（左侧列表项）
    m_categoryList->addItem(tr("General"));
    m_categoryList->addItem(tr("Appearance"));
    m_categoryList->addItem(tr("Advanced"));

    // 为每个分类创建对应的页面（右侧内容）
    // 通用设置页
    QWidget *generalPage = new QWidget(this);
    QVBoxLayout *generalLayout = new QVBoxLayout(generalPage);
    generalLayout->addWidget(new QLabel(tr("General settings will be placed here."), generalPage));
    generalLayout->addStretch();

    // 外观设置页
    QWidget *appearancePage = new QWidget(this);
    QVBoxLayout *appearanceLayout = new QVBoxLayout(appearancePage);
    appearanceLayout->addWidget(
            new QLabel(tr("Appearance settings will be placed here."), appearancePage));
    appearanceLayout->addStretch();

    // 高级设置页
    QWidget *advancedPage = new QWidget(this);
    QVBoxLayout *advancedLayout = new QVBoxLayout(advancedPage);
    advancedLayout->addWidget(
            new QLabel(tr("Advanced settings will be placed here."), advancedPage));
    advancedLayout->addStretch();

    // 将页面添加到堆叠窗口，顺序与列表顺序一致
    m_stackedWidget->addWidget(generalPage);
    m_stackedWidget->addWidget(appearancePage);
    m_stackedWidget->addWidget(advancedPage);
}

void PreferencesDialog::onCategoryChanged(int index)
{
    m_stackedWidget->setCurrentIndex(index);
}

void PreferencesDialog::loadSettings()
{
    // 从 QSettings 读取当前值并更新界面控件
    // 例如：
    // QSettings settings;
    // bool check = settings.value("prefs/option", false).toBool();
    // m_checkBox->setChecked(check);
    // 此处留空，具体实现时添加控件并读写
}

void PreferencesDialog::saveSettings()
{
    // 将界面控件的当前值写入 QSettings
    // 例如：
    // QSettings settings;
    // settings.setValue("prefs/option", m_checkBox->isChecked());
}

void PreferencesDialog::onAccepted()
{
    saveSettings();
    accept();
}

void PreferencesDialog::onApply()
{
    saveSettings();
}

} // namespace hello::app