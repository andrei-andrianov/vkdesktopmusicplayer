#include "customlistwidgetitemview.h"
#include "ui_customlistwidgetitemview.h"

extern QMediaPlayer *player;
extern QMediaPlaylist *playlist;
extern bool *isScrobblingOn;
extern LastFmLoginWidget *lastFmLoginWidget;

CustomListWidgetItemView::CustomListWidgetItemView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomListWidgetItemView)
{
    ui->setupUi(this);
    ui->playButton->setFixedSize(100,100);
    ui->durationBar->setFixedHeight(10);
    ui->durationBar->setTextVisible(true);
    isScrobbled = false;
    //nessessery disconnect for the item to be shown properly
    connect(playlist,SIGNAL(currentMediaChanged(QMediaContent)),this,SLOT(disconnectItem()));
}

CustomListWidgetItemView::~CustomListWidgetItemView()
{
    delete ui;
}
//pass values to the item
void CustomListWidgetItemView::setValues(QString title, QString artist, QUrl audioUrl, int duration, QString lyrics_id, int index, QString TOKEN)
{
    ui->artistLabel->setText(artist);
    ui->titleLabel->setText(title);
    ui->durationBar->setRange(0,duration);
    ui->durationBar->setValue(0);
    ui->durationBar->setFormat(QTime(0, duration/60, duration%60).toString("m:ss"));
    this->LYRICS_ID = lyrics_id;
    this->audioUrl = audioUrl;
    this->index = index;
    this->artist = artist;
    this->title = title;
    this->TOKEN = TOKEN;
    playlist->addMedia(audioUrl);
    ui->titleLabel->setToolTip(title+"\n"+artist);
}

void CustomListWidgetItemView::on_playButton_clicked()
{
    //some (magic)logic for the item
    if (player->state()==QMediaPlayer::PlayingState)
    {
        if (playlist->currentIndex()==index)
        {
            player->pause();
            ui->playButton->setText("▶");
        }
        else
        {
            player->stop();
            playlist->setCurrentIndex(index);
            connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(updatePosition(qint64)));
            player->play();
            sendPlayingNow();
            ui->playButton->setText("❙❙");
        }
    }
    else if (player->state()==QMediaPlayer::StoppedState)
    {
        playlist->setCurrentIndex(index);
        connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(updatePosition(qint64)));
        player->play();
        sendPlayingNow();
        ui->playButton->setText("❙❙");
    }
    else if (player->state()==QMediaPlayer::PausedState)
    {
        if (playlist->currentIndex()==index)
        {
            player->play();
            ui->playButton->setText("❙❙");
        }
        else
        {
            player->stop();
            playlist->setCurrentIndex(index);
            connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(updatePosition(qint64)));
            player->play();
            sendPlayingNow();
            ui->playButton->setText("❙❙");
        }
    }
}
//update the duration bar position
void CustomListWidgetItemView::updatePosition(qint64 pos)
{
    //divide by 1000 to get correct result
    if (pos/1000==ui->durationBar->maximum())
    {
        if (isScrobblingOn&&(!isScrobbled))
        {
            scrobbleTrack();
            isScrobbled = true;
        }
        ui->playButton->setText("▶");
        ui->durationBar->setValue(0);
    }
    ui->durationBar->setValue(pos/1000);
}

void CustomListWidgetItemView::disconnectItem()
{
    if (playlist->currentIndex()==index)
    {
        player->stop();
        connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(updatePosition(qint64)));
        player->play();
        ui->playButton->setText("❙❙");
    }
    else
    {
        player->disconnect(SIGNAL(positionChanged(qint64)));
        ui->durationBar->setValue(0);
        ui->playButton->setText("▶");
    }
}

void CustomListWidgetItemView::showLyrics()
{
    lyricsWidget = new LyricsWidget();
    lyricsWidget->setFixedSize(QSize(320,240));
    lyricsWidget->setWindowTitle(artist+" - "+title);
    lyricsWidget->setToolTip(artist+" - "+title);
    lyricsWidget->show();

    QUrl audioRequest = "https://api.vk.com/method/audio.getLyrics?&access_token="+TOKEN+"&lyrics_id="+LYRICS_ID;
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(audioRequest));
    //server does not answer right away, we have to wait
    QEventLoop wait;
    connect(manager,SIGNAL(finished(QNetworkReply*)),&wait,SLOT(quit()));
    connect(manager,SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    //one take is gonna be 10sec
    QTimer oneTake;
    oneTake.start(10000);
    connect(&oneTake,SIGNAL(timeout()),&wait,SLOT(quit()));
    wait.exec();
    //finally get the reply
    QByteArray byteArrayResponse = reply->readAll();
    reply->deleteLater();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(byteArrayResponse));
    lyricsWidget->setLyrics(jsonDoc.toVariant().toMap().value("response").toMap().value("text").toString());
}
//this method is going to call track.scrobble last.fm API function
void CustomListWidgetItemView::scrobbleTrack()
{
    if (isScrobblingOn)
    {
        //we need to use POST methods for scrobbling API, we also need MD5 hash string
        //it's all described in last.fm API documentation
        uint timestamp = QDateTime::currentMSecsSinceEpoch()/1000;
        QString tempString = "api_key"+lastFmLoginWidget->getAPI_KEY()+"artist"+artist;
        tempString += "methodtrack.scrobblesk"+lastFmLoginWidget->getSESSION_KEY();
        tempString += "timestamp"+QString::number(timestamp)+"track"+title+lastFmLoginWidget->getSHARED_SECRET();
        QByteArray tempArray(tempString.toStdString().c_str());
        QString API_SIG = QString(QCryptographicHash::hash(tempArray,QCryptographicHash::Md5).toHex());
        QUrlQuery postData = QUrlQuery("method=track.scrobble");
        postData.addQueryItem("artist",artist);
        postData.addQueryItem("track",title);
        postData.addQueryItem("timestamp",QString::number(timestamp));
        postData.addQueryItem("api_key",lastFmLoginWidget->getAPI_KEY());
        postData.addQueryItem("api_sig",API_SIG);
        postData.addQueryItem("sk",lastFmLoginWidget->getSESSION_KEY());
        QNetworkAccessManager *manager = new QNetworkAccessManager();
        QNetworkRequest request(QUrl("http://ws.audioscrobbler.com/2.0/?"));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                           "application/x-www-form-urlencoded");
        manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
    }
    else
        return;
}
//this method is going to call track.updateNowPlaying last.fm API function
void CustomListWidgetItemView::sendPlayingNow()
{
    if (isScrobblingOn)
    {
        //we need to use POST methods for scrobbling API, we also need MD5 hash string
        //it's all described in last.fm API documentation
        QString tempString = "api_key"+lastFmLoginWidget->getAPI_KEY()+"artist"+artist;
        tempString += "methodtrack.updateNowPlayingsk"+lastFmLoginWidget->getSESSION_KEY()+"track"+title+lastFmLoginWidget->getSHARED_SECRET();
        QByteArray tempArray(tempString.toStdString().c_str());
        QString API_SIG = QString(QCryptographicHash::hash(tempArray,QCryptographicHash::Md5).toHex());
        QUrlQuery postData = QUrlQuery("method=track.updateNowPlaying");
        postData.addQueryItem("artist",artist);
        postData.addQueryItem("track",title);
        postData.addQueryItem("api_key",lastFmLoginWidget->getAPI_KEY());
        postData.addQueryItem("api_sig",API_SIG);
        postData.addQueryItem("sk",lastFmLoginWidget->getSESSION_KEY());
        QNetworkAccessManager *manager = new QNetworkAccessManager();
        QNetworkRequest request(QUrl("http://ws.audioscrobbler.com/2.0/?"));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                           "application/x-www-form-urlencoded");
        manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
    }
    else
        return;
}

void CustomListWidgetItemView::on_CustomListWidgetItemView_customContextMenuRequested(const QPoint &pos)
{
    QMenu *contextMenu = new QMenu(this);

    QAction *showLyrics = contextMenu->addAction("Lyrics");
    connect(showLyrics,SIGNAL(triggered()),this,SLOT(showLyrics()));

    contextMenu->exec(mapToGlobal(pos));
}
