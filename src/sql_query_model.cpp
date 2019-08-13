#include "sql_query_model.h"


SqlQueryModel::SqlQueryModel(QObject *parent)
    : QSqlQueryModel(parent)
    , m_radius(10)
    , m_color(Qt::red)
    , m_borderColor(Qt::black)
{
}

QHash<int, QByteArray> SqlQueryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    for (int i = 0; i < record().count(); i++) {
        roles.insert(Qt::UserRole + i + 1, record().fieldName(i).toUtf8());
    }
    roles.insert(Qt::UserRole + record().count() + 1, "radius");
    roles.insert(Qt::UserRole + record().count() + 2, "color");
    roles.insert(Qt::UserRole + record().count() + 3, "borderColor");
    return roles;
}

QVariant SqlQueryModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if (index.isValid()) {
        if (role < Qt::UserRole) {
            value = QSqlQueryModel::data(index, role);
        } else if (role == Qt::UserRole + record().count() + 1) {
            value = QVariant::fromValue(m_radius);
        } else if (role == Qt::UserRole + record().count() + 2) {
            value = QVariant::fromValue(m_color);
        } else if (role == Qt::UserRole + record().count() + 3) {
            value = QVariant::fromValue(m_borderColor);
        } else {
            int         columnIdx  = role - Qt::UserRole - 1;
            QModelIndex modelIndex = this->index(index.row(), columnIdx);
            value                  = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
        }
    }
    return value;
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

QColor SqlQueryModel::borderColor() const
{
    return m_borderColor;
}

void SqlQueryModel::setBorderColor(const QColor &color)
{
    m_borderColor = color;
    emit borderColorChanged();
}
