#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbcreator.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlRelation>
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
            createPositionModel();
            createOrganizationModel();
            createTypeWorkingTimeModel();
            createPersonModel();
            createTaimeTrackModel();
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
            createPositionModel();
            createOrganizationModel();
            createTypeWorkingTimeModel();
            createPersonModel();
            createTaimeTrackModel();
            setupView();
        }
    }
}

void MainWindow::sortData()
{
    //TODO Release sortData();
}

void MainWindow::updateModel()
{
    //TODO Release updateModel();
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

void MainWindow::createPositionModel()
{
    m_modelPosition = new QSqlRelationalTableModel(this);
    m_modelPosition->setTable("Position");
    m_modelPosition->select();
}

void MainWindow::createOrganizationModel()
{
    m_modelOrganization = new QSqlRelationalTableModel(this);
    m_modelOrganization->setTable("Organization");
    m_modelOrganization->select();
}

void MainWindow::createTypeWorkingTimeModel()
{
    m_modelTypeWorkingTime = new QSqlRelationalTableModel(this);
    m_modelTypeWorkingTime->setTable("TypeWorkingTime");
    m_modelTypeWorkingTime->select();
}

void MainWindow::createPersonModel()
{
    m_modelPerson = new QSqlRelationalTableModel(this);
    m_modelPerson->setTable("Person");
    m_modelPerson->setRelation(2, QSqlRelation("Organization", "OrganizationID", "Organization"));
    m_modelPerson->setRelation(3, QSqlRelation("Position", "PositionID", "Position"));
    m_modelPerson->select();
}

void MainWindow::createTaimeTrackModel()
{
    m_modelTimeTrack = new QSqlRelationalTableModel(this);
    m_modelTimeTrack->setTable("TimeTrack");
    m_modelTimeTrack->setRelation(1, QSqlRelation("Person", "PersonID", "Person"));
    m_modelTimeTrack->setRelation(4, QSqlRelation("TypeWorkingTime", "TypeWorkingTimeID", "TypeWorkingTime"));
    m_modelTimeTrack->select();
}

void MainWindow::setupView()
{
    ui->tableViewMain->setModel(m_modelTimeTrack);
    ui->tableViewMain->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewMain->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewMain->resizeColumnsToContents();
    ui->tableViewMain->setItemDelegate(new QSqlRelationalDelegate(ui->tableViewMain));
    ui->tableViewMain->horizontalHeader()->setStretchLastSection(true);
}
