#ifndef CUSTOMLISTWIDGETITEMVIEW_H
#define CUSTOMLISTWIDGETITEMVIEW_H

#include <QWidget>
#include <QUrl>
#include <QUrlQuery>
#include "playerwidget.h"
#include <QTime>
#include <QDateTime>
#include <QMediaMetaData>
#include <QImage>
#include <QBitArray>
#include <QByteArray>
#include <QBitmap>
#include <QPixmap>
#include <QCryptographicHash>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>
#include <QDebug>
#include <QMenu>
#include <QCursor>
#include <QAction>
#include "lyricswidget.h"
#include <QJsonDocument>
#include <QVariantList>
#include <QVariantMap>

namespace Ui {
class CustomListWidgetItemView;
}

class CustomListWidgetItemView : public QWidget
{
    Q_OBJECT

public:
    explicit CustomListWidgetItemView(QWidget *parent = 0);
    ~CustomListWidgetItemView();
    void setValues(QString title, QString artist, QUrl audioUrl, int duration,
                   QString LYRICS_ID, int index, QString TOKEN);

private slots:
        void on_playButton_clicked();
        void updatePosition(qint64 pos);
        void disconnectItem();
        void showLyrics();
        void on_CustomListWidgetItemView_customContextMenuRequested(const QPoint &pos);

private:
    Ui::CustomListWidgetItemView *ui;
    QUrl audioUrl;
    QString artist,title, TOKEN, LYRICS_ID;
    bool isScrobbled;
    void scrobbleTrack();
    void sendPlayingNow();
    int index;
    LyricsWidget *lyricsWidget;
};

#endif // CUSTOMLISTWIDGETITEMVIEW_H
