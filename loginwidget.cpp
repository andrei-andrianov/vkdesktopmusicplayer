#include "loginwidget.h"
#include "ui_loginwidget.h"


LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
//Values to get api token
    APP_ID = 5137488;
    PERMISSIONS = "audio";
    DISPLAY = "mobile";
    API_VERSION = "5.40";
    REDIRECT_URI = "https://oauth.vk.com/blank.html";
//Auth string
    authUrl = QUrlQuery("http://api.vkontakte.ru/oauth/authorize?");
    authUrl.addQueryItem("client_id", QString::number(APP_ID));
    authUrl.addQueryItem("scope",PERMISSIONS);
    authUrl.addQueryItem("display", DISPLAY);
    authUrl.addQueryItem("v", API_VERSION);
    authUrl.addQueryItem("redirect_uri", REDIRECT_URI);
    authUrl.addQueryItem("response_type", "token");

    connect(ui->webView,SIGNAL(urlChanged(QUrl)),this,SLOT(fishing(QUrl)));
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
//We are going to fishing if the url is changed to get token
void LoginWidget::fishing(QUrl url)
{
    QUrlQuery url_query;
    url_query.setQuery(url.toString().replace("#","&"));
    TOKEN = url_query.queryItemValue("access_token");
    UID = url_query.queryItemValue("user_id");
    EXPIRES_IN = url_query.queryItemValue("expires_in");
    if (!TOKEN.isEmpty()){
        playerWidget.show();
        playerWidget.setToken(TOKEN);
        playerWidget.setMinimumSize(420,500);
        playerWidget.setMaximumSize(420,500);
        this->close();
    }
}

void LoginWidget::on_pushButton_clicked()
{
    ui->webView->load(authUrl.toString());
}