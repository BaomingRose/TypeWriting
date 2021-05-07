#ifndef GRADEWIDGET_H
#define GRADEWIDGET_H

#include <QWidget>
#include "keyboard.h"

namespace Ui {
class GradeWidget;
}

class GradeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GradeWidget(KeyBoard* kb, QWidget *parent = 0);
    ~GradeWidget();

    KeyBoard* kb;

private slots:
    void on_pushButton_clicked();

public:
    Ui::GradeWidget *ui;
};

#endif // GRADEWIDGET_H
