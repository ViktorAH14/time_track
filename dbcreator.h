#ifndef DBCREATOR_H
#define DBCREATOR_H

#include <QObject>
#include <QSqlDatabase>

class QSqlQuery;

class DBCreator : public QObject
{
    Q_OBJECT
public:
    explicit DBCreator(QObject *parent = 0);
    ~DBCreator();

signals:

public slots:
    bool newTimeTrackDB();

private:
    bool createTimeTrackDB();
    bool checkExec(QSqlQuery query);

    bool createOrganizationTable(QSqlQuery query);
    bool createPositionTable(QSqlQuery query);
    bool createTypeWorkingTimeTable(QSqlQuery query);
    bool createPersonTable(QSqlQuery query);
    bool createTimeTrackTable(QSqlQuery query);

    QSqlDatabase db;
};

#endif // DBCREATOR_H
