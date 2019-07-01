#include "dbcreator.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DBCreator::DBCreator(QObject *parent) : QObject(parent)
{

}

DBCreator::~DBCreator()
{

}

bool DBCreator::newTimeTrackDB()
{
    if (!createTimeTrackDB()) {
        return false;
    }
    return true;
}

bool DBCreator::createTimeTrackDB()
{
    QSqlQuery query;
    query.prepare("PRAGMA foreign_keys = ON;");
    checkExec(query);

    createOrganizationTable(query);
    createPositionTable(query);
    createTypeWorkingTimeTable(query);
    createPersonTable(query);
    createTimeTrackTable(query);

    return true;
}

bool DBCreator::checkExec(QSqlQuery query)
{
    if (!query.exec()) {
        qDebug() << "Error " << query.lastError().text();
        return false;
    }
    return true;
}

bool DBCreator::createOrganizationTable(QSqlQuery query)
{
    query.prepare("CREATE TABLE Organization("
                  "OrganizationID   INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "Organization     TEXT    NOT NULL    UNIQUE)");
    checkExec(query);
    return true;
}

bool DBCreator::createPositionTable(QSqlQuery query)
{
    query.prepare("CREATE TABLE Position("
                  "PositionID   INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "Position     TEXT    NOT NULL    UNIQUE)");
    checkExec(query);
    return true;
}

bool DBCreator::createTypeWorkingTimeTable(QSqlQuery query)
{
    query.prepare("CREATE TABLE TypeWorkingTime("
                  "TypeWorkingTimeID    INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "TypeWorkingTime      TEXT    NOT NULL    UNIQUE, "
                  "Description          TEXT    NOT NULL    UNIQUE)");
    checkExec(query);
    return true;
}

bool DBCreator::createPersonTable(QSqlQuery query)
{
    query.prepare("CREATE TABLE Person("
                  "PersonID         INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "FullName         TEXT    NOT NULL, "
                  "OrganizationID   INTEGER NOT NULL, "
                  "PositionID       INTEGER NOT NULL, "
                  "Recruit          TEXT    NOT NULL, "
                  "GuardNamber      INTEGER, "
                  "Dismissal        TEXT, "
                  "FOREIGN KEY(OrganizationID)  REFERENCES  Organization(OrganizationID), "
                  "FOREIGN KEY(PositionID)      REFERENCES  Position(PositionID))");
    checkExec(query);
    return true;
}

bool DBCreator::createTimeTrackTable(QSqlQuery query)
{
    query.prepare("CREATE TABLE TimeTrack("
                  "TimeTrackID          INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "PersonID             INTEGER NOT NULL, "
                  "Date                 TEXT    NOT NULL, "
                  "Time                 INTEGER NOT NULL, "
                  "TypeWorkingTimeID    INTEGER NOT NULL, "
                  "FOREIGN KEY(PersonID)            REFERENCES  Person(PersonID), "
                  "FOREIGN KEY(TypeWorkingTimeID)   REFERENCES  TypeWorkingTime(TypeWorkingTimeID))");
    checkExec(query);
    return true;
}
