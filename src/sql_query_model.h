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

    double minParamValue() const;
    void   setMinParamValue(double value);

    double maxParamValue() const;
    void   setMaxParamValue(double value);

    int  radius() const;
    void setRadius(int rad);

    QColor color() const;
    void   setColor(const QColor &color);

    QColor additionalColor() const;
    void   setAdditionalColor(const QColor &color);

    QColor borderColor() const;
    void   setBorderColor(const QColor &color);

signals:
    void minParamValueChanged();
    void maxParamValueChanged();
    void radiusChanged();
    void colorChanged();
    void additionalColorChanged();
    void borderColorChanged();

private:
    double m_minParamValue;
    double m_maxParamValue;
    int    m_radius;
    QColor m_color;
    QColor m_additionalColor;
    QColor m_borderColor;
};


#endif // SQL_QUERY_MODEL_H
