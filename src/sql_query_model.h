#ifndef SQL_QUERY_MODEL_H
#define SQL_QUERY_MODEL_H

#include <QColor>
#include <QtQml>
#include <QtSql>


class SqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    using QSqlQueryModel::QSqlQueryModel;

    SqlQueryModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index, int role) const override;

    int  radius() const;
    void setRadius(int rad);

    QColor color() const;
    void   setColor(const QColor &color);

    QColor borderColor() const;
    void   setBorderColor(const QColor &color);

signals:
    void radiusChanged();
    void colorChanged();
    void borderColorChanged();

private:
    int    m_radius;
    QColor m_color;
    QColor m_borderColor;
};


#endif // SQL_QUERY_MODEL_H
