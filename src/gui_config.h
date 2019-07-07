#ifndef GUI_CONFIG_H
#define GUI_CONFIG_H

#include <QtGlobal>

/*!
 \brief Статический класс, хранящий платформозависимые параметры GUI.
 \warning Вносить изменения только в код для той платформы, на которой работаете
 в данный момент!
*/

#ifdef Q_OS_LINUX
class GuiConfig
{
public:
    static constexpr int FONT_SIZE_SMALL  = 8;
    static constexpr int FONT_SIZE_NORMAL = 9;
    static constexpr int FONT_SIZE_BIG    = 10;
    static constexpr int FONT_SIZE_LARGE  = 12;
    static constexpr int FONT_SIZE_HUGE   = 14;

    static constexpr int LAYOUT_MARGIN_SMALL  = 0;
    static constexpr int LAYOUT_MARGIN_NORMAL = 3;
    static constexpr int LAYOUT_MARGIN_BIG    = 6;

    static constexpr int LAYOUT_SPACING_SMALL  = 2;
    static constexpr int LAYOUT_SPACING_NORMAL = 4;
    static constexpr int LAYOUT_SPACING_BIG    = 6;
};
#endif

#ifdef Q_OS_MAC
class GuiConfig
{
public:
    static constexpr int FONT_SIZE_SMALL  = 11;
    static constexpr int FONT_SIZE_NORMAL = 12;
    static constexpr int FONT_SIZE_BIG    = 14;
    static constexpr int FONT_SIZE_LARGE  = 16;
    static constexpr int FONT_SIZE_HUGE   = 18;

    static constexpr int LAYOUT_MARGIN_SMALL  = 0;
    static constexpr int LAYOUT_MARGIN_NORMAL = 3;
    static constexpr int LAYOUT_MARGIN_BIG    = 6;

    static constexpr int LAYOUT_SPACING_SMALL  = 2;
    static constexpr int LAYOUT_SPACING_NORMAL = 4;
    static constexpr int LAYOUT_SPACING_BIG    = 6;
};
#endif

#ifdef Q_OS_WIN
class GuiConfig
{
public:
    static constexpr int FONT_SIZE_SMALL  = 9;
    static constexpr int FONT_SIZE_NORMAL = 10;
    static constexpr int FONT_SIZE_BIG    = 11;
    static constexpr int FONT_SIZE_LARGE  = 13;
    static constexpr int FONT_SIZE_HUGE   = 15;

    static constexpr int LAYOUT_MARGIN_SMALL  = 0;
    static constexpr int LAYOUT_MARGIN_NORMAL = 4;
    static constexpr int LAYOUT_MARGIN_BIG    = 8;

    static constexpr int LAYOUT_SPACING_SMALL  = 2;
    static constexpr int LAYOUT_SPACING_NORMAL = 5;
    static constexpr int LAYOUT_SPACING_BIG    = 8;
};
#endif

#endif // GUI_CONFIG_H
