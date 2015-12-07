#ifndef LASTFMLOGINWIDGET_H
#define LASTFMLOGINWIDGET_H

#include <QWidget>
#include <QUrl>
#include <QCryptographicHash>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <QXmlStreamReader>
#include <QByteArray>

namespace Ui {
class LastFmLoginWidget;
}

class LastFmLoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LastFmLoginWidget(QWidget *parent = 0);
    ~LastFmLoginWidget();
    QString getAPI_KEY();
    QString getSHARED_SECRET();
    QString getSESSION_KEY();
    void getToken();
    void getSession();
    void loadAuthPage();
    bool isAuthorized;

private:
    Ui::LastFmLoginWidget *ui;
    QString API_KEY,SHARED_SECRET,API_SIG,TOKEN,SESSION_KEY;
    QUrl getTokenUrl, authUrl, getSessionUrl;

private slots:
    void debugConsole(QUrl url);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

signals:
    void closed();
};

#endif // LASTFMLOGINWIDGET_H
