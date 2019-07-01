#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbcreator.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
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

void MainWindow::createModel()
{
    m_model = new QSqlTableModel(this);
    m_model->setTable("TimeTrack");
    m_model->select();
}

void MainWindow::setupView()
{
    ui->tableViewMain->setModel(m_model);
    ui->tableViewMain->resizeColumnsToContents();
    ui->tableViewMain->horizontalHeader()->setStretchLastSection(true);
}
