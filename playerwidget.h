#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>

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

private:
    Ui::PlayerWidget *ui;
    QString TOKEN;

private slots:
    void on_pushButton_clicked();
};

#endif // PLAYERWIDGET_H
