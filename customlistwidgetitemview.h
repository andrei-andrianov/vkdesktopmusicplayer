#ifndef CUSTOMLISTWIDGETITEMVIEW_H
#define CUSTOMLISTWIDGETITEMVIEW_H

#include <QWidget>
#include <QUrl>
#include "playerwidget.h"
#include <QTime>

namespace Ui {
class CustomListWidgetItemView;
}

class CustomListWidgetItemView : public QWidget
{
    Q_OBJECT

public:
    explicit CustomListWidgetItemView(QWidget *parent = 0);
    ~CustomListWidgetItemView();
    void setValues(QString title, QString artist, QUrl audioUrl, int duration, double lyrics_id);
private slots:
        void on_playButton_clicked();
        void updatePosition(qint64 pos);
        void disconnectItem();
private:
    Ui::CustomListWidgetItemView *ui;
    QUrl audioUrl;
    double lyrics_id;
};

#endif // CUSTOMLISTWIDGETITEMVIEW_H
