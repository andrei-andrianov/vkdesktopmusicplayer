#include "customlistwidgetitemview.h"
#include "ui_customlistwidgetitemview.h"

CustomListWidgetItemView::CustomListWidgetItemView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomListWidgetItemView)
{
    ui->setupUi(this);
    ui->coverView->setFixedSize(100,100);
    ui->playButton->setFixedSize(35,35);
    ui->durationBar->setVisible(false);
}

CustomListWidgetItemView::~CustomListWidgetItemView()
{
    delete ui;
}

void CustomListWidgetItemView::setValues(QString title, QString artist, QUrl audioUrl)
{
    ui->artistLabel->setText(artist);
    ui->titleLabel->setText(title);
    this->audioUrl = audioUrl;
}

void CustomListWidgetItemView::on_playButton_clicked()
{
    ui->artistLabel->setText(audioUrl.toString());
    ui->durationBar->setVisible(true);
    ui->horizontalSpacer->~QSpacerItem();
}
