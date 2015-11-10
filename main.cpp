#include "loginwidget.h"
#include "playerwidget.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWidget loginWidget;

    loginWidget.setMinimumSize(420,500);
    loginWidget.setMaximumSize(420,500);

    loginWidget.show();

    return a.exec();
}
