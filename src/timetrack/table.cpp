#include "table.h"

#include <QSqlRelationalTableModel>
#include <QSqlDatabase>
#include <QSqlRelationalDelegate>
#include <QStringList>
#include <QSqlRelation>
#include <QStyleOption>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

Table::Table(QSqlDatabase *db, const QString &tableName, QObject *parent) : QObject(parent)
{
    m_model = new QSqlRelationalTableModel(0);
    m_model->setTable(tableName);
    names = new QStringList();
}

Table::~Table()
{
    delete m_model;
    delete names;
}

bool Table::openTable()
{
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if (!m_model->select())
        return false;
    names->clear();
    for (int i = 0; i < m_model->columnCount(); i++)
        names->append(m_model->headerData(i, Qt::Horizontal).toString());
    return true;
}

int Table::rowsCount()
{
    return m_model->rowCount();
}

int Table::columnIndex(const QString &column)
{
    return m_model->fieldIndex(column);
}

bool Table::setTableValue(int row, const QString &fieldName, const QVariant &value)
{
    return setTableValue(row, m_model->fieldIndex(fieldName), value);
}

bool Table::setTableValue(int row, int column, const QVariant &value)
{
    return m_model->setData(m_model->index(row, column), value);
}

QVariant Table::getTableValue(int row, const QString &fieldName)
{
    return getTableValue(row, m_model->fieldIndex(fieldName));
}

QVariant Table::getTableValue(int row, int column)
{
    return m_model->data(m_model->index(row, column));
}

void Table::renameColumn(const QString &oldName, const QString &newName)
{
    this->setTableColumnName(names->indexOf(oldName), newName);
}

bool Table::save()
{
    if (!m_model->submitAll()) {
        criticalMessage();
        return false;
    }
    return true;
}

bool Table::newRow()
{
    m_model->submitAll();
    m_model->setFilter("");
    m_model->select();
    if (!m_model->insertRow(0)) {
        return false;
    }
    return true;
}

void Table::deleteRow(int row)
{
    if (!m_model->removeRow(row)) {
        criticalMessage();
    }
}

void Table::setTableColumnName(int index, const QString &name)
{
    m_model->setHeaderData(index, Qt::Horizontal, name);
}

QString Table::getColumnName(int column)
{
    return names->value(column);
}

void Table::addRelation(int column, const QString &extTable, const QString &extKey, const QString &extDisplay)
{
    QSqlRelation rel(extTable, extKey, extDisplay);
    m_model->setRelation(column,rel);
}

void Table::addRelation(const QString &column, const QString &extTable, const QString &extKey, const QString &extDisplay)
{
    addRelation(this->columnIndex(column), extTable, extKey, extDisplay);
}

void Table::canselChanges()
{
    m_model->revertAll();
}

bool Table::selectRows(const QString &where)
{
    m_model->setFilter(where);
    m_model->select();
    return (m_model->rowCount() > 0);
}

void Table::criticalMessage()
{
    QMessageBox msg;
    msg.setText(trUtf8("Error"));
    msg.setInformativeText(m_model->lastError().text());
    msg.setIcon(QMessageBox::Critical);
    msg.exec();
}

