#include "reportform.h"
#include "ui_reportform.h"

ReportForm::ReportForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportForm)
{
    ui->setupUi(this);
}

ReportForm::~ReportForm()
{
    delete ui;
}
