#include "viewcatalogform.h"
#include "ui_viewcatalogform.h"

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
