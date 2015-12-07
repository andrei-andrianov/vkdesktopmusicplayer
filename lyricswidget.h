#ifndef LYRICSWIDGET_H
#define LYRICSWIDGET_H

#include <QWidget>

namespace Ui {
class LyricsWidget;
}

class LyricsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LyricsWidget(QWidget *parent = 0);
    ~LyricsWidget();
    void setLyrics(QString lyrics);

private:
    Ui::LyricsWidget *ui;
};

#endif // LYRICSWIDGET_H
