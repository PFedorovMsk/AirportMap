#ifndef GRAPHSHEET_H
#define GRAPHSHEET_H

#include <QPen>


/*!
 \brief Структура для хранения кривой.

 Содержит сами данные (точки), а также информацию о том, как кривая должна рисоваться и подписываться.
*/

struct GCurve {
    //! \brief Конструктор.
    GCurve();

    /*!
     \brief Имя, которое будет отображаться в легенде.

     Если number == 1, то возвращает строку name без изменений.

     Иначе добавляет порядковый номер в конец (не меняя поле name).
    */
    QString fullName() const;

    QVector<double> x;      /*!< Массив координат \f$x\f$ точек \f$p = (x,y)\f$. */
    QVector<double> y;      /*!< Массив координат \f$y\f$ точек \f$p = (x,y)\f$. */
    QString         name;   /*!< Название кривой. */
    int             number; /*!< Количество кривых с таким же названием. */
    QPen            pen; /*!< Экземпляр QPen, которым будет рисоваться кривая. */
    bool            visible; /*!< Видимость кривой (отображается или скрыта?) */
};

/*!
 \brief Структура для хранения границ осей координат.
*/

struct GAxisRange {
    double xMin; /*!< Левая граница оси OX. */
    double xMax; /*!< Правая граница оси OX. */
    double yMin; /*!< Нижняя граница оси OY. */
    double yMax; /*!< Верхняя граница оси OY. */
};


/*!
 \brief Класс, реализующий "страницу" окна графиков.

 Хранит в себе данные всех кривых, отображаемых на странице и предоставляет пользователю возможности
 настройки отображения.

 Ничего не рисует, только работает с данными. Отрисовкой занимается GraphWindow.
*/

class GraphSheet
{

public:
    //! \brief Конструктор.
    GraphSheet();

    //! \brief Деструктор.
    ~GraphSheet();

    //! \brief Удаляет все пользовательские данные, устанавливает значения по-умолчанию.
    void clear();

    //! \brief Возвращает подпись для оси OX.
    const QString &xLabel() const;

    //! \brief Возвращает подпись для оси OY.
    const QString &yLabel() const;

    //! \brief Возвращает заголовок страницы.
    const QString &titleLabel() const;

    //! \brief Возвращает подзаголовок страницы.
    const QString &subTitleLabel() const;

    //! \brief Возвращает текущие значения границ осей координат.
    const GAxisRange &axisRange() const;

    //! \brief Возвращает информацию о том, вычисляются границы осей координат автоматически или нет.
    bool autoCalcRanges() const;

    //! \brief Возвращает ссылку на массив кривых.
    const QVector<GCurve> &curves() const;

    //! \brief Устанавливает подпись для оси OX.
    void setXLabel(const QString &label);

    //! \brief Устанавливает подпись для оси OY.
    void setYLabel(const QString &label);

    //! \brief Устанавливает заголовок страницы.
    void setTitleLabel(const QString &label);

    //! \brief Устанавливает подзаголовок страницы.
    void setSubTitleLabel(const QString &label);

    /*!
     \brief Устанавливает метод работы с границами осей координат.

     \param autoCalc - если true, то границы считаются автоматически, иначе - берутся
     введенные пользователем вручную данные.
    */
    void setAutoCalcRanges(bool autoCalc);

    /*!
     \brief Сохраняет пользовательские границы осей координат.
    */
    void setAxisRange(const GAxisRange &axisRange);

    /*!
     \brief Устанавливает видимость кривой.

     \param index - номер кривой в массиве.
     \param visible - если true, то кривая будет отображаться, иначе - скрыта.
    */
    void setCurveVisible(int index, bool visible);


    /*!
     \brief Добавляет новую кривую.

     \param x - массив координат \f$x\f$ точек \f$p = (x,y)\f$.
     \param y - массив координат \f$y\f$ точек \f$p = (x,y)\f$.
     \param name - название кривой.
     \param pen - экземпляр QPen, которым будет рисоваться кривая.
     \param visible - видимость кривой (отображается или скрыта?)
    */
    void addCurve(const QVector<double> &x, const QVector<double> &y, const QString &name, const QPen &pen,
                  bool visible = true);


private:
    /*!
     \brief Устанавливает границы осей координат.

     Если m_autoCalcRanges == true, то вычисляет их, пробегая по всем точкам всех кривых.

     Иначе берет их из m_userAxisRange.

     Результат сохраняется в m_axisRange, который возвращается при вызове axisRange().

    */
    void calcRanges();


private:
    QVector<GCurve> m_curves;
    QString         m_xLabel;
    QString         m_yLabel;
    QString         m_titleLabel;
    QString         m_subTitleLabel;
    bool            m_autoCalcRanges;
    GAxisRange      m_axisRange;
    GAxisRange      m_userAxisRange;
};


#endif // GRAPHSHEET_H
