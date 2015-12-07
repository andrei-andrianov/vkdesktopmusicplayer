#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
//values to get api token
    APP_ID = 5137488;
    PERMISSIONS = "audio";
    DISPLAY = "mobile";
    API_VERSION = "5.40";
    REDIRECT_URI = "https://oauth.vk.com/blank.html";
//auth string
    authUrl = QUrlQuery("http://api.vkontakte.ru/oauth/authorize?");
    authUrl.addQueryItem("client_id", QString::number(APP_ID));
    authUrl.addQueryItem("scope",PERMISSIONS);
    authUrl.addQueryItem("display", DISPLAY);
    authUrl.addQueryItem("v", API_VERSION);
    authUrl.addQueryItem("redirect_uri", REDIRECT_URI);
    authUrl.addQueryItem("response_type", "token");

    connect(ui->loginView,SIGNAL(urlChanged(QUrl)),this,SLOT(fishing(QUrl)));
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

QString LoginWidget::getToken()
{
    return TOKEN;
}

QString LoginWidget::getUID()
{
    return UID;
}

QString LoginWidget::getEXPIRES_IN()
{
    return EXPIRES_IN;
}
//we are going to fishing if the url is changed to get token
void LoginWidget::fishing(QUrl url)
{
    QUrlQuery url_query;
    url_query.setQuery(url.toString().replace("#","&"));
    TOKEN = url_query.queryItemValue("access_token");
    UID = url_query.queryItemValue("user_id");
    EXPIRES_IN = url_query.queryItemValue("expires_in");
    if (!TOKEN.isEmpty()){
        playerWidget = new PlayerWidget();
        playerWidget->setToken(TOKEN);
        playerWidget->setUID(UID);
        playerWidget->setExpires_in(EXPIRES_IN);
        playerWidget->setMinimumSize(450,500);
        playerWidget->setMaximumSize(450,500);
        playerWidget->show();
        this->close();
        playerWidget->createPlaylistView();
        this->destroy();
    }
}

void LoginWidget::on_loginButton_clicked()
{
    ui->loginView->load(authUrl.toString());
}
