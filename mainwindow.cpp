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

    organizationForm = new ViewCatalogForm(this);
    organizationForm->setWindowTitle(trUtf8("Organization form"));

    positionForm = new ViewCatalogForm(this);
    positionForm->setWindowTitle(trUtf8("Position form"));

    typeworkingtimeForm = new ViewCatalogForm(this);
    typeworkingtimeForm->setWindowTitle(trUtf8("Type working time form"));

    personForm = new ViewCatalogForm(this);
    personForm->setWindowTitle(trUtf8("Person form"));
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
    organizationForm->exec();
    if (!personMapper.isNull()) {
        personMapper->reloadRelations();
        personMapper->refresh();
    }
}

void MainWindow::showPositionForm()
{
    positionForm->exec();
    if (!personMapper.isNull()) {
        personMapper->reloadRelations();
        personMapper->refresh();
    }
}

void MainWindow::showTypeWorkingTimeForm()
{
    typeworkingtimeForm->exec();
    if (!timetrackMapper.isNull()) {
        timetrackMapper->reloadRelations();
        timetrackMapper->refresh();
    }
}

void MainWindow::showPersonForm()
{
    personForm->exec();
    if (!timetrackMapper.isNull()) {
        timetrackMapper->reloadRelations();
        timetrackMapper->refresh();
    }
}

void MainWindow::addRecord()
{
    if (!timetrackMapper.isNull()) {
        timetrackMapper->newRow();
    }
}

void MainWindow::deleteRecord()
{
    if (!timetrackMapper.isNull()) {
        int row = ui->tableViewMain->currentIndex().row();
        if (row >= 0) {
            timetrackMapper->deleteRow(row);
        }
    }
}

void MainWindow::cancelChange()
{

}

void MainWindow::save()
{
    if (!timetrackMapper.isNull()) {
        ui->tableViewMain->submit();
        timetrackMapper->save();
    }
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
     organizationForm->setMapper(organizationMapper);
     positionForm->setMapper(positionMapper);
     typeworkingtimeForm->setMapper(typeworkingtimeMapper);
     personForm->setMapper(personMapper);

    timetrackMapper->setView(ui->tableViewMain);
    timetrackMapper->refresh();
    timetrackMapper->setColumnName(0, trUtf8("Time track ID"));
    timetrackMapper->setColumnName(1, trUtf8("Person"));
    timetrackMapper->setColumnName(2, trUtf8("Date"));
    timetrackMapper->setColumnName(3, trUtf8("Time"));
    timetrackMapper->setColumnName(4, trUtf8("Type working time ID"));
//    ui->tableViewMain->hideColumn(0);
    ui->tableViewMain->resizeColumnsToContents();
    ui->tableViewMain->horizontalHeader()->setStretchLastSection(true);
}
