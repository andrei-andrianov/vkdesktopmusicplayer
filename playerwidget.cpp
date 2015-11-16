#include "playerwidget.h"
#include "ui_playerwidget.h"

PlayerWidget::PlayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerWidget)
{
    ui->setupUi(this);
    CustomListWidgetItemView *view = new CustomListWidgetItemView();
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(QSize(310,115));
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item,view);
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
    getPlaylist();
    parseJson();
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

void PlayerWidget::parseJson()
{
//    QJsonDocument jsonDocument = QJsonDocument::fromBinaryData(byteArrayPlaylist);
//    QVariantList variantListPlaylist = jsonDocument.toVariant();
//    qDebug()<<"length="+variantListPlaylist.length();
}
