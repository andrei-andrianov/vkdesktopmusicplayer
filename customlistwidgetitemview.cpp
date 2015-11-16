#include "customlistwidgetitemview.h"
#include "ui_customlistwidgetitemview.h"

CustomListWidgetItemView::CustomListWidgetItemView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomListWidgetItemView)
{
    ui->setupUi(this);
    ui->coverView->setFixedSize(100,100);
    ui->playButton->setFixedSize(35,35);
}

CustomListWidgetItemView::~CustomListWidgetItemView()
{
    delete ui;
}
