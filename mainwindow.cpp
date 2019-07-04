#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbcreator.h"
#include "table.h"
#include "tableiomapper.h"
#include "viewcatalogform.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    deleteModel();
}

void MainWindow::newDB()
{
    QFileDialog fd;
    fd.setDefaultSuffix("db");
    fd.setWindowTitle(trUtf8("New database"));
    fd.setFileMode(QFileDialog::AnyFile);
    fd.setNameFilter(trUtf8("Database (*.db)"));
    if (fd.exec() == QDialog::Accepted) {
        if (fd.selectedFiles().count() > 0) {
            dbName = fd.selectedFiles().at(0);
            setWindowTitle(trUtf8("Time tracking - ") + dbName);
            createDB(dbName);
            createModel();
            setupView();
        }
    }
}

void MainWindow::openDB()
{
    QFileDialog fd;
    fd.setDefaultSuffix("db");
    fd.setWindowTitle(trUtf8("Open database"));
    fd.setFileMode(QFileDialog::AnyFile);
    fd.setNameFilter(trUtf8("Database (*.db)"));
    if (fd.exec() == QDialog::Accepted) {
        if (fd.selectedFiles().count() > 0) {
            dbName = fd.selectedFiles().at(0);
            setWindowTitle(trUtf8("Time tracking - ") + dbName);
            connectDB(dbName);
            createModel();
            setupView();
        }
    }
}

void MainWindow::showOrganizationForm()
{

}

void MainWindow::showPositionForm()
{

}

void MainWindow::showTypeWorkingTimeForm()
{

}

void MainWindow::showPersonForm()
{

}

void MainWindow::addRecord()
{

}

void MainWindow::deleteRecord()
{

}

void MainWindow::cancelChange()
{

}

void MainWindow::save()
{

}

bool MainWindow::connectDB(const QString &dbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName(dbName);
    if (!db.open()) {
        QMessageBox::critical(this, trUtf8("Error"), db.lastError().text());
        return false;
    }
    return true;
}

bool MainWindow::createDB(const QString &dbName)
{
    if (!connectDB(dbName)) {
        return false;
    }
    DBCreator db;
    if (!db.newTimeTrackDB()) {
        QMessageBox::critical(this, trUtf8("Error"), trUtf8("Unable to create database."));
        return false;
    }
    return true;
}

void MainWindow::createModel()
{
    deleteModel();

    organization = new Table(0, "Organization");
    organization->openTable();
    organizationMapper = new TableIOMapper(organization);

    position = new Table(0, "Position");
    position->openTable();
    positionMapper = new TableIOMapper(position);

    typeworkingtime = new Table(0, "TypeWorkingTime");
    typeworkingtime->openTable();
    typeworkingtimeMapper = new TableIOMapper(typeworkingtime);

    person = new Table(0, "Person");
    person->openTable();
    person->addRelation("OrganizationID", "Organization", "OrganizationID", "Organization");
    person->addRelation("PositionID", "Position", "PositionID", "Position");
    personMapper = new TableIOMapper(person);

    timetrack = new Table(0, "TimeTrack");
    timetrack->openTable();
    timetrack->addRelation("PersonID", "Person", "PersonID", "FullName");
    timetrack->addRelation("TypeWorkingTimeID", "TypeWorkingTime", "TypeWorkingTimeID", "TypeWorkingTime");
    timetrackMapper = new TableIOMapper(timetrack);

}

void MainWindow::deleteModel()
{
    delete organizationMapper;
    delete positionMapper;
    delete typeworkingtimeMapper;
    delete personMapper;
    delete timetrackMapper;

    delete organization;
    delete position;
    delete typeworkingtime;
    delete person;
    delete timetrack;
}

void MainWindow::setupView()
{

}
