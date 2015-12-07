#include "playerwidget.h"
#include "ui_playerwidget.h"

QMediaPlayer *player;
QMediaPlaylist *playlist;
bool *isScrobblingOn;
LastFmLoginWidget *lastFmLoginWidget;

PlayerWidget::PlayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerWidget)
{
    ui->setupUi(this);
    player = new QMediaPlayer();
    playlist = new QMediaPlaylist(player);
    player->setVolume(50);
    player->setPlaylist(playlist);
    ui->volumeSlider->setRange(0,100);
    ui->volumeSlider->setValue(50);
    ui->scrobbleButton->setEnabled(false);
    isScrobblingOn = false;
    //connect volume bar
    connect(ui->volumeSlider,SIGNAL(valueChanged(int)),player,SLOT(setVolume(int)));
}

PlayerWidget::~PlayerWidget()
{
    delete ui;
}

void PlayerWidget::setToken(QString token)
{
    TOKEN = token;
}

void PlayerWidget::setUID(QString uid)
{
    UID = uid;
}

void PlayerWidget::setExpires_in(QString expires_in)
{
    EXPIRES_IN = expires_in;
}

void PlayerWidget::createPlaylistView()
{
    //api request for playlist
    getPlaylist();
    //json response parsing
    QJsonDocument jsonDocument = QJsonDocument::fromJson(byteArrayPlaylist);
    QVariantList variantListPlaylist = jsonDocument.toVariant().toMap().value("response").toList();
    if (!variantListPlaylist.isEmpty())
        for (int i=0;i<variantListPlaylist.size();i++)
        {
            QVariantMap current = variantListPlaylist[i].toMap();
            //insert custom list widget item
            CustomListWidgetItemView *view = new CustomListWidgetItemView();
            QListWidgetItem *item = new QListWidgetItem;
            view->setValues(current.value("title").toString(),current.value("artist").toString(),
                            current.value("url").toUrl(),current.value("duration").toInt(),
                            current.value("lyrics_id").toString(),i,TOKEN);
            item->setSizeHint(QSize(305,115));
//            item->setToolTip(current.value("title").toString()+"\n"+current.value("artist").toString());
            ui->listWidget->addItem(item);
            ui->listWidget->setItemWidget(item,view);
        }
}

//REST GET request
void PlayerWidget::getPlaylist()
{
    QUrl audioRequest = "https://api.vk.com/method/audio.get?uid="+UID+"&access_token="+TOKEN;
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
    byteArrayPlaylist = reply->readAll();
    reply->deleteLater();
}

void PlayerWidget::on_scrobbleButton_clicked()
{
    if (!isScrobblingOn)
    {
        isScrobblingOn = new bool(true);
        ui->scrobbleButton->setText("Scrobbling ON");
    }
    else
    {
        isScrobblingOn = false;
        ui->scrobbleButton->setText("Scrobbling OFF");
    }
}

void PlayerWidget::on_lasfmButton_clicked()
{
    lastFmLoginWidget = new LastFmLoginWidget();
    lastFmLoginWidget->setMinimumSize(450,500);
    lastFmLoginWidget->setMaximumSize(450,500);
    lastFmLoginWidget->show();
    lastFmLoginWidget->getToken();
    lastFmLoginWidget->loadAuthPage();
    connect(lastFmLoginWidget,SIGNAL(closed()),this,SLOT(lastFmWidgetClosed()));
}

void PlayerWidget::lastFmWidgetClosed()
{
    if (lastFmLoginWidget->isAuthorized)
    {
        ui->scrobbleButton->setEnabled(true);
        ui->lasfmButton->setEnabled(false);
        ui->lasfmButton->setText("Logged in last.fm");
        lastFmLoginWidget->getSession();
    }
    disconnect(lastFmLoginWidget,SIGNAL(closed()),this,SLOT(lastFmWidgetClosed()));
}

void PlayerWidget::on_aboutButton_clicked()
{
    AboutWidget *aboutWidget = new AboutWidget();
    aboutWidget->setFixedSize(QSize(240,350));
    aboutWidget->show();
}
