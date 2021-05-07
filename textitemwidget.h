#ifndef TEXTITEMWIDGET_H
#define TEXTITEMWIDGET_H

#include "keyboard.h"
#include <QWidget>

namespace Ui {
class TextItemWidget;
}

class TextItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TextItemWidget(QString text, QWidget *parent = 0);
    ~TextItemWidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TextItemWidget *ui;
};

#endif // TEXTITEMWIDGET_H
