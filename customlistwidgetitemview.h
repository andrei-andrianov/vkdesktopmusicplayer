#ifndef CUSTOMLISTWIDGETITEMVIEW_H
#define CUSTOMLISTWIDGETITEMVIEW_H

#include <QWidget>
#include <QUrl>

namespace Ui {
class CustomListWidgetItemView;
}

class CustomListWidgetItemView : public QWidget
{
    Q_OBJECT

public:
    explicit CustomListWidgetItemView(QWidget *parent = 0);
    ~CustomListWidgetItemView();
    void setValues(QString title, QString artist, QUrl audioUrl);
private slots:
        void on_playButton_clicked();
private:
    Ui::CustomListWidgetItemView *ui;
    QUrl audioUrl;
};

#endif // CUSTOMLISTWIDGETITEMVIEW_H
