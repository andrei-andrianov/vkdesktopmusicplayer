#include "aboutwidget.h"
#include "ui_aboutwidget.h"

AboutWidget::AboutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWidget)
{
    ui->setupUi(this);
    QString aboutText = "<h2 align=\"center\">VK Desktop Music Player</h2>";
    aboutText += "<p align=\"center\"><i>Version: 0.1</i></p>";
    aboutText += "<p align=\"center\"></p>";
    aboutText += "<p align=\"center\"><b>Authors:</b></p>";
    aboutText += "<p align=\"center\">Andrianov Andrei</p>";
    aboutText += "<p align=\"center\">Markowitsch Georg</p>";
    aboutText += "<p align=\"center\"></p>";
    aboutText += "<p align=\"center\"><a href=https://vk.com/dev/main>vk.com API</a></p>";
    aboutText += "<p align=\"center\"><a href=http://www.last.fm/api/intro>last.fm API</a></p>";
    ui->aboutLabel->setText(aboutText);
}

AboutWidget::~AboutWidget()
{
    delete ui;
}
