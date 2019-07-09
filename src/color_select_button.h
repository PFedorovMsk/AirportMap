#ifndef COLOR_SELECT_BUTTON_H
#define COLOR_SELECT_BUTTON_H

#include <QColor>
#include <QPushButton>


class ColorSelectButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ColorSelectButton(QWidget *parent = nullptr);

    void setColor(const QColor &color);

    const QColor &color() const;

public slots:
    void updateColor();
    void changeColor();

private:
    QColor m_color;
};

#endif // COLOR_SELECT_BUTTON_H
