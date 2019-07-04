#include "qupdateableview.h"

#include <QPainter>
#include <QPaintEvent>

QUpdateableView::QUpdateableView(QWidget *parent) : QTableView(parent)
{

}

void QUpdateableView::submit()
{
    QModelIndex index = currentIndex();
    currentChanged(index, index);
}

