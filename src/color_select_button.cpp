#include "color_select_button.h"
#include <QColorDialog>


ColorSelectButton::ColorSelectButton(QWidget *parent)
    : QPushButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(changeColor()));
}

void ColorSelectButton::setColor(const QColor &color)
{
    m_color = color;
    updateColor();
}

const QColor &ColorSelectButton::color() const
{
    return m_color;
}

void ColorSelectButton::updateColor()
{
    setStyleSheet("background-color: " + m_color.name());
}

void ColorSelectButton::changeColor()
{
    QColor newColor = QColorDialog::getColor(m_color, parentWidget(), "Выбор цвета", QColorDialog::ShowAlphaChannel);
    if (newColor.isValid() && newColor != m_color) {
        setColor(newColor);
    }
}
