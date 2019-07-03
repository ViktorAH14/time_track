#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>

class QSqlRelationalTableModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void newDB();
    void openDB();
    void sortData();
    void updateModel();

private:
    Ui::MainWindow *ui;

    bool connectDB(const QString &dbName);
    bool createDB(const QString &dbName);
    void createPositionModel();
    void createOrganizationModel();
    void createTypeWorkingTimeModel();
    void createPersonModel();
    void createTaimeTrackModel();
    void setupView();

    QString dbName;
    QSqlRelationalTableModel *m_modelPosition;
    QSqlRelationalTableModel *m_modelOrganization;
    QSqlRelationalTableModel *m_modelTypeWorkingTime;
    QSqlRelationalTableModel *m_modelPerson;
    QSqlRelationalTableModel *m_modelTimeTrack;
};

#endif // MAINWINDOW_H
