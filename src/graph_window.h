#ifndef GRAPH_WINDOW_H
#define GRAPH_WINDOW_H

#include "src/font_manager.h"
#include "src/graph_sheet.h"
#include "src/gui_config.h"
#include "third_party/qcustomplot/qcustomplot.h"
#include <QAction>
#include <QFileDialog>
#include <QFontDatabase>
#include <QFrame>
#include <QMainWindow>
#include <QMenu>
#include <QPen>


/*!
 \brief Класс, реализующий окно для просмотра графиков.
*/

class GraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! \brief Конструктор.
    explicit GraphWindow(QWidget *parent = nullptr);

    //! \brief Деструктор.
    ~GraphWindow();

    //! \brief Возвращает количество страниц.
    int countSheets() const;

    //! \brief Возвращает ссылку на страницу с номером index.
    GraphSheet &sheet(int index);

    //! \brief Возвращает ссылку страницу, котороая отображается в данный момент.
    GraphSheet &currentSheet();

    //! \brief Устанавливает количество страниц
    void setCountSheets(int count);

    //! \brief Обновляет поле рисовальщика QCustomPlot (заставляет перерисовать себя).
    void updatePlotter();


public slots:
    //! \brief Удаляет пользовательские данные, устанавливает значения по-умолчанию.
    void onClear();


private slots:
    //! \brief Реакция на выделение какого-либо объекта мышью на поле рисовальщика.
    void onSelectionChanged();

    //! \brief Реакция на клик мыши по полю рисовальщика.
    void onMousePress();

    //! \brief Реакция на движение мыши.
    void onMouseWheel();

    /*!
     \brief Вызывает контекстное меню.
     \details Слот. Реакция на клик правой кнопкой мыши внутри поля рисовальщика.
    */
    void onMenuRequest(QPoint pos);

    //! \brief Перемещает окно легенды внутри поля рисовальщика.
    void onMoveLegend();

    /*!
    \brief Сохраняет изображение.

        Открывает диалог сохранения для выбора пути и имени файла.

        \todo Расширение ".png" не добавляется к концу имени файла автоматически. Надо запилить.
    */
    void onSavePng();

    //! \brief Передает информацию о том, нужно ли автоматически вычислять границы осей координат, в GraphSheet.
    void onSetAutoRanges(bool checked);

    //! \brief Скрывает выбранную кривую (из главного меню).
    void onHideCurve(QAction *action);

    //! \brief Скрывает выбранную кривую (из контекстного).
    void onHideCurveFromContextMenu();

    //! \brief Показывает выбранную скрытую кривую.
    void onShowCurve(QAction *action);

    //! \brief Перерисовыет содержимое поля рисовальщика при смене страницы (из меню).
    void onCurrentSheetChanged(QAction *action);


private:
    /*!
     \brief Загружает шрифты и устанавливает их параметры (начертание, размер и т.д.).
     \see FontManager.
    */
    void loadFonts();

    //! \brief Устанавливает расположение всех элементов на виджете.
    void initLayouts();

    //! \brief Инициализирует элементы QAction меню.
    void initActions();

    //! \brief Инициализирует главное меню и связывает элементы с соответствующими QActions.
    void initMenus();

    //! \brief Инициализирует поле рисовальщика QCustomPlot.
    void initPlotter();

    //! \brief Обновляет элементы главного меню при необходимости.
    void updateMenu();


private:
    QVector<GraphSheet> m_sheets;
    GraphSheet *        m_currentSheet;
    QCustomPlot *       m_plotter;

    QFont m_plotterTitleFont;
    QFont m_plotterSubTitleFont;
    QFont m_plotterLegendFont;
    QFont m_plotterAxesLabelFont;
    QFont m_plotterAxesTickLabelFont;

    QAction *m_actionSavePng;
    QAction *m_actionSetAutoRanges;

    QMenu *m_menuFile;
    QMenu *m_menuView;
    QMenu *m_menuSheet;
    QMenu *m_menuShow;
    QMenu *m_menuHide;
};


#endif // GRAPH_WINDOW_H
