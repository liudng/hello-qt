// SPDX-FileCopyrightText: 2026 Liu Dong <liudng@hotmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later OR LGPL-3.0-or-later

#pragma once

#include <QDialog>
#include <QMap>
#include <QHash>

#include "abstractpreferencepage.h"

class QListWidget;
class QStackedWidget;
class QDialogButtonBox;

class QTreeWidget;
class QTreeWidgetItem;
class AbstractPreferencePage;

namespace hello::app {

class PreferencesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PreferencesDialog(QWidget *parent = nullptr);
    ~PreferencesDialog();
    void addPage(AbstractPreferencePage *page);

protected:
    // 重写显示事件：在对话框完全显示前，统一调用所有页面的加载配置逻辑
    void showEvent(QShowEvent *event) override;

private slots:
    // 左侧树节点切换时的响应
    void onPageChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    // 底部按钮点击响应
    void onAccept();
    void onApply();

private:
    void setupUi(); // 纯代码构建容器界面
    void applyChanges(); // 遍历所有页面执行保存

    // UI 控件
    QTreeWidget *m_categoryTree;
    QStackedWidget *m_pageStack;
    QDialogButtonBox *m_buttonBox;

    // 数据映射：维护 树节点 -> 页面接口 的对应关系
    QMap<QTreeWidgetItem *, AbstractPreferencePage *> m_pageMap;

    // 防止重复加载的标志位
    bool m_loaded;
};

} // namespace hello::app