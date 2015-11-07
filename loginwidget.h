#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QUrlQuery>
#include <QDebug>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
    bool isLogged;

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginWidget *ui;
    int APP_ID;
    QString PERMISSIONS,DISPLAY,API_VERSION,REDIRECT_URI;
    QString TOKEN, UID, EXPIRES_IN;
    QUrlQuery authUrl;
public slots:
    void fishing(QUrl url);
};

#endif // LOGINWIDGET_H
