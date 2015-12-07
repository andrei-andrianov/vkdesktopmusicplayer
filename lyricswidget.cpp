#include "lyricswidget.h"
#include "ui_lyricswidget.h"

LyricsWidget::LyricsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LyricsWidget)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

LyricsWidget::~LyricsWidget()
{
    delete ui;
}

void LyricsWidget::setLyrics(QString lyrics)
{
    ui->textEdit->setText(lyrics);
}
