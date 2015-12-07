#include "loginwidget.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    //to avoid some problems in songs names
    QTextCodec *utfCodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utfCodec);

    QApplication a(argc, argv);
    LoginWidget loginWidget;

    loginWidget.setMinimumSize(420,520);
    loginWidget.setMaximumSize(420,520);

    loginWidget.show();

    return a.exec();
}
