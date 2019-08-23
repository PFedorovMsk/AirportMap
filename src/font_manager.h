#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <QFont>
#include <QFontDatabase>

/*!
 \brief Статический класс для работы с загружаемыми из файлов шрифтами
 (singleton).
*/

class FontManager
{
public:
    //! \brief Возвращает (единственный) экземпляр FontManager.
    static FontManager &instance();

    FontManager(const FontManager &) = delete;
    FontManager &operator=(FontManager &) = delete;

    //! \brief Возвращает шрифт с обычным начертанием размера pointSize.
    QFont regular(int pointSize = 9) const;

    //! \brief Возвращает наклонный шрифт размера pointSize.
    QFont regularItalic(int pointSize = 9) const;

    //! \brief Возвращает жирный шрифт размера pointSize.
    QFont regularBold(int pointSize = 9) const;

    //! \brief Возвращает жирный наклонный шрифт размера pointSize.
    QFont regularBoldItalic(int pointSize = 9) const;

    //! \brief Возвращает моноширинный шрифт с обычным начертанием размера
    //! pointSize.
    QFont mono(int pointSize = 9) const;

    //! \brief Возвращает моноширинный наклонный шрифт размера pointSize.
    QFont monoItalic(int pointSize = 9) const;

    //! \brief Возвращает моноширинный жирный шрифт размера pointSize.
    QFont monoBold(int pointSize = 9) const;

    //! \brief Возвращает моноширинный жирный наклонный шрифт размера pointSize.
    QFont monoBoldItalic(int pointSize = 9) const;

private:
    /*!
     \brief Конструктор.

     Загружает шрифты из файлов (fonts в корневой директории проекта) в базу и
     привязывает к ним идентификаторы для поиска.
    */
    FontManager();

    /*!
     \brief Находит нужный шрифт и настраивает его свойства.

     \param id - идентификатор шрифта.
     \param size - размер кегля.
     \param bold - шрифт с жирным начертанием или нет.
     \param italic - шрифт с наклонным начертанием или нет.
     \return экземпляр шрифта с выставленными свойствами.
    */
    static QFont getFont(int id, int size, bool bold, bool italic);

private:
    int m_regularId;
    int m_regularItalicId;
    int m_regularBoldId;
    int m_regularBoldItalicId;

    int m_monoId;
    int m_monoItalicId;
    int m_monoBoldId;
    int m_monoBoldItalicId;
};

#endif // FONTMANAGER_H
