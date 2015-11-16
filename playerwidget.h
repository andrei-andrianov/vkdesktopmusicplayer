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
#include <QJsonObject>


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
    void parseJson();

private slots:
};

#endif // PLAYERWIDGET_H
