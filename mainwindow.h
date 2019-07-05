#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>

namespace Ui {
class MainWindow;
}

class Table;
class TableIOMapper;
class ViewCatalogForm;

typedef QPointer<Table> TablePtr;
typedef QPointer<TableIOMapper> TableMapperPtr;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void newDB();
    void openDB();

    void showOrganizationForm();
    void showPositionForm();
    void showTypeWorkingTimeForm();
    void showPersonForm();

    void addRecord();
    void deleteRecord();
    void cancelChanges();
    void save();

private:
    Ui::MainWindow *ui;

    bool connectDB(const QString &dbName);
    bool createDB(const QString &dbName);
    void createModel();
    void deleteModel();
    void setupView();

    TablePtr organization;
    TablePtr position;
    TablePtr typeworkingtime;
    TablePtr person;
    TablePtr timetrack;

    TableMapperPtr organizationMapper;
    TableMapperPtr positionMapper;
    TableMapperPtr typeworkingtimeMapper;
    TableMapperPtr personMapper;
    TableMapperPtr timetrackMapper;

    ViewCatalogForm *organizationForm;
    ViewCatalogForm *positionForm;
    ViewCatalogForm *typeworkingtimeForm;
    ViewCatalogForm *personForm;

    QString dbName;
};

#endif // MAINWINDOW_H
