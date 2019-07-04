#include "tableiomapper.h"

#include <QDataWidgetMapper>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QAbstractItemView>
#include <QSqlRelation>

TableIOMapper::TableIOMapper(Table *table, QObject *parent) : QObject(parent)
{
    m_table = table;
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(table->m_model);
    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    mapper->setItemDelegate(new QSqlRelationalDelegate());
}

TableIOMapper::~TableIOMapper()
{
    delete mapper;
}

