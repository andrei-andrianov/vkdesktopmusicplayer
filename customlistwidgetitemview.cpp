#include "customlistwidgetitemview.h"
#include "ui_customlistwidgetitemview.h"

extern QMediaPlayer *player;

CustomListWidgetItemView::CustomListWidgetItemView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomListWidgetItemView)
{
    ui->setupUi(this);
    ui->coverView->setFixedSize(100,100);
    ui->playButton->setFixedSize(35,35);
    ui->durationBar->setFixedHeight(10);
    ui->durationBar->setTextVisible(true);
    connect(player,SIGNAL(mediaChanged(QMediaContent)),this,SLOT(disconnectItem()));
}

CustomListWidgetItemView::~CustomListWidgetItemView()
{
    delete ui;
}

void CustomListWidgetItemView::setValues(QString title, QString artist, QUrl audioUrl, int duration, double lyrics_id)
{
    ui->artistLabel->setText(artist);
    ui->titleLabel->setText(title);
    ui->durationBar->setRange(0,duration);
    ui->durationBar->setValue(0);
    ui->durationBar->setFormat(QTime(0, duration/60, duration%60).toString("m:ss"));
    this->lyrics_id = lyrics_id;
    this->audioUrl = audioUrl;
}

void CustomListWidgetItemView::on_playButton_clicked()
{
    if (player->state()==QMediaPlayer::PlayingState)
    {
        if (player->media().resources()[0].url()==audioUrl)
        {
            player->pause();
            ui->playButton->setText(">");
        }
        else
        {
            player->stop();
            player->setMedia(audioUrl);
            connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(updatePosition(qint64)));
            player->play();
            ui->playButton->setText("||");
        }
    }
    else if (player->state()==QMediaPlayer::StoppedState)
    {
        player->setMedia(audioUrl);
        connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(updatePosition(qint64)));
        player->play();
        ui->playButton->setText("||");
    }
    else if (player->state()==QMediaPlayer::PausedState)
    {
        if (player->media().resources()[0].url()==audioUrl)
        {
            player->play();
            ui->playButton->setText("||");
        }
        else
        {
            player->stop();
            player->setMedia(audioUrl);
            connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(updatePosition(qint64)));
            player->play();
            ui->playButton->setText("||");
        }
    }
}

void CustomListWidgetItemView::updatePosition(qint64 pos)
{
    ui->durationBar->setValue(pos/1000);
    qDebug()<<pos/1000;
}

void CustomListWidgetItemView::disconnectItem()
{
    player->disconnect(SIGNAL(positionChanged(qint64)));
    ui->durationBar->setValue(0);
}
