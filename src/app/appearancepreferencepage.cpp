// SPDX-FileCopyrightText: 2026 Liu Dong <liudng@hotmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later OR LGPL-3.0-or-later

#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QSettings>
#include <QStyleFactory>
#include <QApplication>
#include <QIcon>
#include <QDir>
#include <QDirIterator>
#include <QStandardPaths>
#include <QSet>
#include <QLocale>

#include "appearancepreferencepage.h"

namespace hello::app {

AppearancePreferencePage::AppearancePreferencePage(QWidget *parent) : QWidget(parent)
{
    // 最外层布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 提示信息
    QLabel *infoLabel =
            new QLabel(tr("Changes will be applied after restarting the application."), this);
    infoLabel->setStyleSheet("color: gray; font-style: italic;");
    mainLayout->addWidget(infoLabel);

    // --- 1. 创建外观设置分组 ---
    QGroupBox *appearanceGroup = new QGroupBox(tr("Appearance"), this);
    QFormLayout *formLayout = new QFormLayout(appearanceGroup);

    // 2. 初始化控件

    // 界面语言
    m_languageCombo = new QComboBox(this);
    m_languageCombo->addItem(tr("System Default"), ""); // 显示文本, 实际保存的数据
    // 动态获取可用的翻译语言
    QStringList availableLanguages = getAvailableLanguages();
    for (const QString &langCode : availableLanguages) {
        QString langName = QLocale(langCode).nativeLanguageName();
        // Capitalize the first letter for better display
        if (!langName.isEmpty()) {
            langName[0] = langName[0].toUpper();
        }
        m_languageCombo->addItem(langName, langCode);
    }
    formLayout->addRow(tr("Language:"), m_languageCombo);

    // 应用样式
    m_styleCombo = new QComboBox(this);
    m_styleCombo->addItem(tr("Default"), ""); // 默认样式由系统决定
    // 动态获取当前平台支持的 Qt 样式 (如 Fusion, Windows)
    QStringList styleKeys = QStyleFactory::keys();
    for (const QString &style : styleKeys) {
        m_styleCombo->addItem(style, style); // 保存样式名称作为数据
    }
    formLayout->addRow(tr("Style:"), m_styleCombo);

    // Icon 主题
    m_iconThemeCombo = new QComboBox(this);
    m_iconThemeCombo->addItem(tr("Default"), "");
    // 调用扫描函数获取系统实际主题
    QStringList systemThemes = getAvailableIconThemes();
    for (const QString &theme : systemThemes) {
        // 避免重复添加，虽然 getAvailableIconThemes 内部已用 QSet 去重
        if (m_iconThemeCombo->findData(theme) == -1) {
            m_iconThemeCombo->addItem(theme, theme);
        }
    }
    formLayout->addRow(tr("Icon Theme:"), m_iconThemeCombo);

    mainLayout->addWidget(appearanceGroup);
    mainLayout->addStretch(1); // 底部弹簧，保持控件顶部对齐
}

/**
 * @brief 应用指定的语言翻译
 *
 * @param langCode 语言代码，如 "zh_CN" 或空字符串表示系统默认
 */
void AppearancePreferencePage::applyLanguage(const QString &langCode)
{
    // 移除旧的翻译器
    if (m_translator) {
        qApp->removeTranslator(m_translator);
        delete m_translator;
        m_translator = nullptr;
    }
    
    // 如果不是系统默认，加载新翻译
    if (!langCode.isEmpty()) {
        m_translator = new QTranslator(this);
        if (m_translator->load(QLocale(langCode), "hello", "_", ":/i18n")) {
            qApp->installTranslator(m_translator);
        } else {
            delete m_translator;
            m_translator = nullptr;
        }
    }
}

/**
 * @brief 从 Qt 资源系统获取可用的翻译语言列表
 *
 * 扫描 :/i18n 目录下的 .qm 翻译文件，提取语言代码
 * 这些文件由 CMake 的 qt_add_translations 自动生成
 */
QStringList AppearancePreferencePage::getAvailableLanguages() const
{
    QStringList languages;
    QDir i18nDir(":/i18n");
    if (i18nDir.exists()) {
        QStringList filters;
        filters << "*.qm";
        QFileInfoList files = i18nDir.entryInfoList(filters, QDir::Files);
        for (const QFileInfo &file : files) {
            // 文件名格式: hello_zh_CN.qm, 提取语言代码 zh_CN
            QString fileName = file.baseName(); // 去掉扩展名
            if (fileName.startsWith("hello_")) {
                QString langCode = fileName.mid(6); // 去掉 "hello_" 前缀
                languages << langCode;
            }
        }
    }
    return languages;
}

/**
 * @brief 扫描系统标准目录，获取实际可用的 Icon 主题列表
 *
 * 遵循 Freedesktop.org Icon Theme 规范：
 * 1. ~/.icons (用户级)
 * 2. ~/.local/share/icons (用户级 XDG)
 * 3. /usr/share/icons (系统级 XDG)
 * 4. XDG_DATA_DIRS 中定义的其他目录下的 icons 子目录
 *
 * 判定一个目录为 Icon 主题的依据：该目录下存在 index.theme 文件
 */
QStringList AppearancePreferencePage::getAvailableIconThemes() const
{
    QSet<QString> themes;
    QStringList searchPaths;

    // 1. 用户目录 ~/.icons
    searchPaths << QDir::homePath() + "/.icons";

    // 2. 用户目录 ~/.local/share/icons
    searchPaths << QDir::homePath() + "/.local/share/icons";

    // 3. 系统目录 /usr/share/icons
    searchPaths << "/usr/share/icons";

    // 4. 从 XDG_DATA_DIRS 读取其他系统目录
    // QStandardPaths::GenericDataLocation 对应 XDG_DATA_DIRS
    QStringList xdgPaths = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation);
    for (const QString &p : xdgPaths) {
        QString iconPath = p + "/icons";
        if (!searchPaths.contains(iconPath)) {
            searchPaths << iconPath;
        }
    }

    // 扫描这些路径
    for (const QString &path : searchPaths) {
        QDir dir(path);
        if (!dir.exists())
            continue;

        // 获取该目录下的所有子目录
        QStringList dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        for (const QString &dirName : dirs) {
            // 规范要求：主题目录下必须包含 index.theme 文件
            QString themeFile = path + "/" + dirName + "/index.theme";
            if (QFile::exists(themeFile)) {
                // 排除一些特殊的缓存目录
                if (dirName != "default" && !dirName.startsWith("hicolor")) {
                    themes.insert(dirName);
                }
            }
        }
    }

    // 转换为 QStringList 并排序，让下拉框看起来更整齐
    QStringList list = themes.values();
    list.sort();
    return list;
}

QString AppearancePreferencePage::title() const
{
    return tr("Appearance");
}

QWidget *AppearancePreferencePage::widget()
{
    return this;
}

void AppearancePreferencePage::loadSettings()
{
    QSettings settings;

    // 读取配置，如果不存在则使用默认值
    // 1. 语言
    QString langCode = settings.value("appearance/language", "").toString();
    int langIndex = m_languageCombo->findData(langCode);
    m_languageCombo->setCurrentIndex(langIndex >= 0 ? langIndex : 0);

    // 2. 样式
    QString styleName = settings.value("appearance/style", "").toString();
    int styleIndex = m_styleCombo->findData(styleName);
    m_styleCombo->setCurrentIndex(styleIndex >= 0 ? styleIndex : 0);

    // 3. Icon 主题
    QString iconTheme = settings.value("appearance/iconTheme", "").toString();
    int iconIndex = m_iconThemeCombo->findData(iconTheme);
    if (iconIndex >= 0) {
        m_iconThemeCombo->setCurrentIndex(iconIndex);
    } else {
        // 如果配置文件里的主题不在列表里，直接显示在文本框中
        m_iconThemeCombo->setEditText(iconTheme);
    }
}

void AppearancePreferencePage::saveSettings()
{
    QSettings settings;

    // 保存配置。使用 currentData() 保存内部数据，而不是显示的文本
    QString langCode = m_languageCombo->currentData().toString();
    settings.setValue("appearance/language", langCode);
    
    // 立即应用语言更改
    applyLanguage(langCode);
    
    QString styleName = m_styleCombo->currentData().toString();
    settings.setValue("appearance/style", styleName);

    QApplication::setStyle(QStyleFactory::create(styleName));
    QString iconTheme = m_iconThemeCombo->currentData().toString();
    settings.setValue("appearance/iconTheme", iconTheme);
    QIcon::setThemeName(iconTheme);
}

} // namespace hello::app