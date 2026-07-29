// SPDX-FileCopyrightText: 2026 Liu Dong <liudng@hotmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later OR LGPL-3.0-or-later

#include <QVBoxLayout>
#include <QLabel>

#include "centralwidget.h"

namespace hello::app {

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel(tr("Hello, World!"), this);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 20px; color: green;");
    layout->addWidget(label);
}

} // namespace hello::app