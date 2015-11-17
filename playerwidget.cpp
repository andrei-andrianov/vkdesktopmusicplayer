#include "playerwidget.h"
#include "ui_playerwidget.h"

QMediaPlayer *player;

PlayerWidget::PlayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerWidget)
{
    ui->setupUi(this);
    player = new QMediaPlayer();
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
            view->setValues(current.value("title").toString(),current.value("artist").toString(),current.value("url").toUrl(),current.value("duration").toInt(),current.value("lyrics_id").toDouble());
            item->setSizeHint(QSize(305,115));
            ui->listWidget->addItem(item);
            ui->listWidget->setItemWidget(item,view);
        }
}
//post-get
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
