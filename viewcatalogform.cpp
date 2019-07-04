#include "viewcatalogform.h"
#include "ui_viewcatalogform.h"
#include "tableiomapper.h"

ViewCatalogForm::ViewCatalogForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewCatalogForm)
{
    ui->setupUi(this);
}

ViewCatalogForm::~ViewCatalogForm()
{
    delete ui;
}

void ViewCatalogForm::setMapper(TableIOMapper *mapper)
{
    this->mapper = mapper;
    mapper->setView(ui->tableView);
    mapper->setColumnName(0, windowTitle());
    ui->tableView->setColumnWidth(0, 270);
    //    ui->tableView->hideColumn(1);
}

void ViewCatalogForm::addItem()
{
    if (!mapper.isNull())
        mapper->newRow();
}

void ViewCatalogForm::deleteItem()
{
    if (!mapper.isNull())
        mapper->deleteRow(ui->tableView->currentIndex().row());
}

void ViewCatalogForm::save()
{
    if (!mapper.isNull()) {
//        ui->tableView->submit(); BUG ui->tableView-.submit();
        mapper->save();
    }
}
