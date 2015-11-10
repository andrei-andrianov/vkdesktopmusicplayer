#include "playerwidget.h"
#include "ui_playerwidget.h"

PlayerWidget::PlayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerWidget)
{
    ui->setupUi(this);
}

PlayerWidget::~PlayerWidget()
{
    delete ui;
}

void PlayerWidget::setToken(QString token)
{
    TOKEN = token;
}

void PlayerWidget::on_pushButton_clicked()
{
    ui->label->setText(TOKEN);
}
