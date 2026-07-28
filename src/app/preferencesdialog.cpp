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
#include <QSplitter>
#include <QTreeWidget>
#include <QAbstractButton>
#include <QShowEvent>

#include "preferencesdialog.h"

namespace hello::app {

PreferencesDialog::PreferencesDialog(QWidget *parent) : QDialog(parent), m_loaded(false)
{
    setWindowTitle(tr("Preferences"));
    setModal(true);
    setMinimumSize(600, 400);

    // 1. 创建左侧分类树
    m_categoryTree = new QTreeWidget(this);
    m_categoryTree->setHeaderHidden(true); // 隐藏表头
    m_categoryTree->setRootIsDecorated(false); // 不显示展开/折叠的小箭头

    // 2. 创建右侧页面堆栈
    m_pageStack = new QStackedWidget(this);
    // 添加一个空白的占位页面，防止一开始没有任何页面时报错
    m_pageStack->addWidget(new QWidget());

    // 3. 使用 QSplitter 让左右两栏可以拖拽调整大小 (体验更好)
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(m_categoryTree);
    splitter->addWidget(m_pageStack);
    splitter->setStretchFactor(0, 1); // 左侧占比小
    splitter->setStretchFactor(1, 3); // 右侧占比大
    splitter->setChildrenCollapsible(false); // 不允许完全拖拽折叠

    // 4. 创建底部确定/取消/应用按钮
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel
                                               | QDialogButtonBox::Apply,
                                       Qt::Horizontal, this);

    // 5. 组装整体布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(splitter);
    mainLayout->addWidget(m_buttonBox);

    // 6. 连接信号槽
    connect(m_categoryTree, &QTreeWidget::currentItemChanged, this,
            &PreferencesDialog::onPageChanged);

    // OK 按钮触发 accept
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, &PreferencesDialog::onAccept);
    // Cancel 按钮触发 reject
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    // 处理 Apply 按钮 (需要判断点击的是哪个按钮)
    connect(m_buttonBox, &QDialogButtonBox::clicked, this, [this](QAbstractButton *button) {
        if (m_buttonBox->buttonRole(button) == QDialogButtonBox::ApplyRole) {
            onApply();
        }
    });
}

PreferencesDialog::~PreferencesDialog() = default;

void PreferencesDialog::addPage(AbstractPreferencePage *page)
{
    if (!page)
        return;

    // 1. 添加左侧树节点
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(m_categoryTree);
    treeItem->setText(0, page->title());

    // 2. 获取页面实际 Widget 并添加到右侧堆栈
    QWidget *pageWidget = page->widget();
    m_pageStack->addWidget(pageWidget);

    // 3. 建立映射关系
    m_pageMap[treeItem] = page;

    // 4. 如果是添加的第一个页面，默认选中它
    if (m_categoryTree->topLevelItemCount() == 1) {
        m_categoryTree->setCurrentItem(treeItem);
        m_pageStack->setCurrentWidget(pageWidget);
    }
}

void PreferencesDialog::onPageChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous);
    if (m_pageMap.contains(current)) {
        m_pageStack->setCurrentWidget(m_pageMap[current]->widget());
    }
}

void PreferencesDialog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    // 确保只在第一次显示时加载配置，避免反复弹出对话框时重复加载
    if (!m_loaded) {
        for (AbstractPreferencePage *page : m_pageMap) {
            page->loadSettings();
        }
        m_loaded = true;
    }
}

void PreferencesDialog::onApply()
{
    applyChanges();
    // Apply 按钮通常不关闭对话框，只保存数据
}

void PreferencesDialog::onAccept()
{
    applyChanges();
    accept(); // 关闭对话框并返回 QDialog::Accepted
}

void PreferencesDialog::applyChanges()
{
    // 遍历所有已注册的页面，调用其保存逻辑
    for (AbstractPreferencePage *page : m_pageMap) {
        page->saveSettings();
    }
}

} // namespace hello::app