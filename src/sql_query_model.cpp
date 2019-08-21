#include "sql_query_model.h"


SqlQueryModel::SqlQueryModel(QObject *parent)
    : QSqlQueryModel(parent)
    , m_minParamValue(0.0)
    , m_maxParamValue(100.0)
    , m_radius(10)
    , m_color(Qt::red)
    , m_additionalColor(Qt::red)
    , m_borderColor(Qt::black)
{
}

QHash<int, QByteArray> SqlQueryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    for (int i = 0; i < record().count(); i++) {
        roles.insert(Qt::UserRole + i + 1, record().fieldName(i).toUtf8());
    }

    roles.insert(Qt::UserRole + record().count() + 1, "minParamValue");
    roles.insert(Qt::UserRole + record().count() + 2, "maxParamValue");
    roles.insert(Qt::UserRole + record().count() + 3, "radius");
    roles.insert(Qt::UserRole + record().count() + 4, "color");
    roles.insert(Qt::UserRole + record().count() + 5, "additionalColor");
    roles.insert(Qt::UserRole + record().count() + 6, "borderColor");

    return roles;
}

QVariant SqlQueryModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if (index.isValid()) {
        if (role < Qt::UserRole) {
            value = QSqlQueryModel::data(index, role);
        } else if (role == Qt::UserRole + record().count() + 1) {
            value = QVariant::fromValue(m_minParamValue);
        } else if (role == Qt::UserRole + record().count() + 2) {
            value = QVariant::fromValue(m_maxParamValue);
        } else if (role == Qt::UserRole + record().count() + 3) {
            value = QVariant::fromValue(m_radius);
        } else if (role == Qt::UserRole + record().count() + 4) {
            value = QVariant::fromValue(m_color);
        } else if (role == Qt::UserRole + record().count() + 5) {
            value = QVariant::fromValue(m_additionalColor);
        } else if (role == Qt::UserRole + record().count() + 6) {
            value = QVariant::fromValue(m_borderColor);
        } else {
            int         columnIdx  = role - Qt::UserRole - 1;
            QModelIndex modelIndex = this->index(index.row(), columnIdx);
            value                  = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
        }
    }
    return value;
}

double SqlQueryModel::minParamValue() const
{
    return m_minParamValue;
}

void SqlQueryModel::setMinParamValue(double value)
{
    m_minParamValue = value;
    emit minParamValueChanged();
}

double SqlQueryModel::maxParamValue() const
{
    return m_maxParamValue;
}

void SqlQueryModel::setMaxParamValue(double value)
{
    m_maxParamValue = value;
    emit maxParamValueChanged();
}

int SqlQueryModel::radius() const
{
    return m_radius;
}

void SqlQueryModel::setRadius(int rad)
{
    m_radius = rad;
    emit radiusChanged();
}

QColor SqlQueryModel::color() const
{
    return m_color;
}

void SqlQueryModel::setColor(const QColor &color)
{
    m_color = color;
    emit colorChanged();
}

QColor SqlQueryModel::additionalColor() const
{
    return m_additionalColor;
}

void SqlQueryModel::setAdditionalColor(const QColor &color)
{
    m_additionalColor = color;
    emit additionalColorChanged();
}

QColor SqlQueryModel::borderColor() const
{
    return m_borderColor;
}

void SqlQueryModel::setBorderColor(const QColor &color)
{
    m_borderColor = color;
    emit borderColorChanged();
}
