#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QVariant>

class QSqlRelationalTableModel;
class QSqlDatabase;
class QStringList;

class Table : public QObject
{
    Q_OBJECT

public:
    Table(QSqlDatabase *db, const QString &tableName);
    ~Table();

    bool openTable();
    int rowsCount();
    int columnIndex(const QString &column);
    bool setTableValue(int row, const QString &fieldName, const QVariant &value);
    bool setTableValue(int row, int column, const QVariant &value);
    QVariant getTableValue(int row, const QString &fieldName);
    QVariant getTableValue(int row, int column);
    void renameColumn(const QString &oldName, const QString &newName);
    bool save();
    bool newRow();
    void deleteRow(int row);
    void setTableColumnName(int index, const QString &name);
    void setColumnHidden(int index, bool hidden);
    QString getColumnName(int column);
    void addRelation(int column, const QString &extTable, const QString &extKey, const QString &extDisplay);
    //Call only after opening the table.
    void addRelation(const QString &column, const QString &extTable, const QString &extKey, const QString &extDisplay);
    void canselChanges();
    bool selectRows(const QString &where);

protected:
    friend class TableIOMapper;

    QSqlRelationalTableModel *m_model;
    QStringList *names;
};

#endif // TABLE_H
