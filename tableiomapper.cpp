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

bool TableIOMapper::selectRow(int num)
{
    mapper->setCurrentIndex(num);
    return mapper->currentIndex() == num;
}

bool TableIOMapper::selectNextRow()
{
    return selectRow(currentRow() + 1);
}

bool TableIOMapper::selectPrevRow()
{
    return selectRow(currentRow() - 1);
}

void TableIOMapper::selectFirstRow()
{
    mapper->toFirst();
}

void TableIOMapper::selectLastRow()
{
    mapper->toLast();
}

int TableIOMapper::rowsCount()
{
    return mapper->model()->rowCount();
}

int TableIOMapper::currentRow()
{
    return mapper->currentIndex();
}

void TableIOMapper::addDataWidget(QWidget *widget, int column)
{
    mapper->addMapping(widget, column);
}

void TableIOMapper::addDataWidget(QWidget *widget, const QString &columnName)
{
    addDataWidget(widget, m_table->columnIndex(columnName));
}

void TableIOMapper::addRelationalComboBox(QComboBox *comboBox, int column)
{
    if (m_table->m_model->relation(column).isValid()) {
        QSqlTableModel *m = m_table->m_model->relationModel(column);
        comboBox->setModel(m);
        comboBox->setModelColumn(m->fieldIndex(m_table->m_model->relation(column).displayColumn()));
        mapper->addMapping(comboBox, column);
    } else {
        mapper->addMapping(comboBox, column, "currentItem");
    }
}

void TableIOMapper::addRelationalComboBox(QComboBox *comboBox, const QString &columnName)
{
    addRelationalComboBox(comboBox, m_table->columnIndex(columnName));
}

void TableIOMapper::reloadRelation(QComboBox *comboBox)
{
    QSqlTableModel *m = (QSqlTableModel *)(comboBox->model());
    m->select();
}

void TableIOMapper::reloadRelations()
{
    for (int i = 0; i < m_table->m_model->columnCount(); i++) {
        QSqlTableModel *m = m_table->m_model->relationModel(i);
        if (m) {
            m->select();
        }
    }
}

void TableIOMapper::clearDataWidgets()
{
    mapper->clearMapping();
}

void TableIOMapper::setView(QAbstractItemView *view)
{
    view->setModel(m_table->m_model);
    view->setItemDelegate(new QSqlRelationalDelegate());
}

void TableIOMapper::setColumnName(int column, const QString &name)
{
    m_table->setTableColumnName(column, name);
}

void TableIOMapper::newRow()
{
    m_table->newRow();
    selectRow(0);
}

void TableIOMapper::save()
{
    m_table->save();
}

void TableIOMapper::canselChanges()
{
    m_table->canselChanges();
}

void TableIOMapper::refresh()
{
    m_table->selectRows("");
}

void TableIOMapper::deleteRow(int num)
{
    if (num > 0)
        m_table->deleteRow(num);
}

