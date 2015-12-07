#include "lastfmloginwidget.h"
#include "ui_lastfmloginwidget.h"

LastFmLoginWidget::LastFmLoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LastFmLoginWidget)
{
    ui->setupUi(this);
    isAuthorized = false;
    API_KEY = "e9b5b66922ea96b054cdd47001ad753b";
    SHARED_SECRET = "56c340c1f8800cc6856875a9aaf96e5c";
    getTokenUrl = QUrl("http://ws.audioscrobbler.com/2.0/?method=auth.gettoken&api_key="+API_KEY);
    connect(ui->webView,SIGNAL(urlChanged(QUrl)),this,SLOT(debugConsole(QUrl)));
}

LastFmLoginWidget::~LastFmLoginWidget()
{
    delete ui;
}

QString LastFmLoginWidget::getAPI_KEY()
{
    return API_KEY;
}

QString LastFmLoginWidget::getSHARED_SECRET()
{
    return SHARED_SECRET;
}

QString LastFmLoginWidget::getSESSION_KEY()
{
    return SESSION_KEY;
}

void LastFmLoginWidget::getToken()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(getTokenUrl));
    QEventLoop wait;
    connect(manager,SIGNAL(finished(QNetworkReply*)),&wait,SLOT(quit()));
    connect(manager,SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    //one take is gonna be 10sec
    QTimer oneTake;
    oneTake.start(10000);
    connect(&oneTake,SIGNAL(timeout()),&wait,SLOT(quit()));
    wait.exec();
    //finally get the reply
    QByteArray byteArrayToken = reply->readAll();
    reply->deleteLater();
    //parse xml response
    QXmlStreamReader xmlReader;
    xmlReader.addData(byteArrayToken);
    while (!(xmlReader.name().toString()=="token"))
        xmlReader.readNext();
    TOKEN = xmlReader.readElementText();
    qDebug()<< TOKEN;
    authUrl = QUrl("http://www.last.fm/api/auth/?api_key=" + API_KEY + "&token=" + TOKEN);
}

void LastFmLoginWidget::getSession()
{
    QString tempString = "api_key" + API_KEY + "methodauth.getsessiontoken" + TOKEN + SHARED_SECRET;
    QByteArray tempArray(tempString.toStdString().c_str());
    API_SIG = QString(QCryptographicHash::hash(tempArray,QCryptographicHash::Md5).toHex());
    getSessionUrl = QUrl("http://ws.audioscrobbler.com/2.0/?method=auth.getsession&token=" + TOKEN + "&api_key=" + API_KEY + "&api_sig=" + API_SIG);
    qDebug()<< getSessionUrl.toString()+" <-SESSION URL";
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(getSessionUrl));
    QEventLoop wait;
    connect(manager,SIGNAL(finished(QNetworkReply*)),&wait,SLOT(quit()));
    connect(manager,SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    //one take is gonna be 10sec
    QTimer oneTake;
    oneTake.start(10000);
    connect(&oneTake,SIGNAL(timeout()),&wait,SLOT(quit()));
    wait.exec();
    //finally get the reply
    QByteArray byteArrayToken = reply->readAll();
    reply->deleteLater();
    //parse xml response
    QXmlStreamReader xmlReader;
    xmlReader.addData(byteArrayToken);
    while (!(xmlReader.name().toString()=="key"))
        xmlReader.readNext();
    SESSION_KEY = xmlReader.readElementText();
    qDebug()<< SESSION_KEY+" <-SESSION HASH";
}

void LastFmLoginWidget::loadAuthPage()
{
    ui->webView->load(authUrl);
}

void LastFmLoginWidget::debugConsole(QUrl url)
{
    qDebug()<<url.toString();
}

void LastFmLoginWidget::on_buttonBox_accepted()
{
    isAuthorized = true;
    emit closed();
    this->close();
}

void LastFmLoginWidget::on_buttonBox_rejected()
{
    isAuthorized = false;
    emit closed();
    this->close();
}
