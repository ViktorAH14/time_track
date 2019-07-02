#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSqlTableModel;

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
    void createModel();
    void setupView();

    QString dbName;
    QSqlTableModel *m_model;
};

#endif // MAINWINDOW_H
