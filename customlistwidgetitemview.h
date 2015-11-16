#ifndef CUSTOMLISTWIDGETITEMVIEW_H
#define CUSTOMLISTWIDGETITEMVIEW_H

#include <QWidget>

namespace Ui {
class CustomListWidgetItemView;
}

class CustomListWidgetItemView : public QWidget
{
    Q_OBJECT

public:
    explicit CustomListWidgetItemView(QWidget *parent = 0);
    ~CustomListWidgetItemView();

private:
    Ui::CustomListWidgetItemView *ui;
};

#endif // CUSTOMLISTWIDGETITEMVIEW_H
