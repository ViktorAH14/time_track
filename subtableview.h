#ifndef SUBTABLEVIEW_H
#define SUBTABLEVIEW_H

#include <QDialog>

class QSqlTableModel;

namespace Ui {
class SubTableView;
}

class SubTableView : public QDialog
{
    Q_OBJECT

public:
    explicit SubTableView(const QString &tableName, const QString &columnName, QWidget *parent = 0);
    ~SubTableView();

signals:
    void modelChanged();

private slots:
    void addRow();
    void saveRecord();
    void deleteRecord();

private:
    Ui::SubTableView *ui;

    void createModel();
    void setupView();

    QSqlTableModel *m_model;
    QString m_tableName;
    QString m_columnName;
};

#endif // SUBTABLEVIEW_H
