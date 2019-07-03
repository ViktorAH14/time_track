#ifndef VIEWCATALOGFORM_H
#define VIEWCATALOGFORM_H

#include <QDialog>

namespace Ui {
class ViewCatalogForm;
}

class ViewCatalogForm : public QDialog
{
    Q_OBJECT

public:
    explicit ViewCatalogForm(QWidget *parent = 0);
    ~ViewCatalogForm();

private:
    Ui::ViewCatalogForm *ui;
};

#endif // VIEWCATALOGFORM_H
