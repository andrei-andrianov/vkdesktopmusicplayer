#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include "customlistwidgetitemview.h"
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <QJsonDocument>
#include <QVariantList>
#include <QVariantMap>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "lastfmloginwidget.h"
#include "aboutwidget.h"

namespace Ui {
class PlayerWidget;
}

class PlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = 0);
    ~PlayerWidget();
    void setToken(QString token);
    void setUID(QString uid);
    void setExpires_in(QString expires_in);
    void createPlaylistView();

private:
    Ui::PlayerWidget *ui;
    QString TOKEN, UID, EXPIRES_IN;
    QByteArray byteArrayPlaylist;
    void getPlaylist();

private slots:
    void on_scrobbleButton_clicked();
    void on_lasfmButton_clicked();
    void lastFmWidgetClosed();
    void on_aboutButton_clicked();
};

#endif // PLAYERWIDGET_H
