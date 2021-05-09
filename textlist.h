#ifndef TEXTLIST_H
#define TEXTLIST_H

#include <QWidget>
#include <QListWidget>
#include "keyboard.h"
#include "gradewidget.h"
#include "regardtable.h"

namespace Ui {
class TextList;
}

class TextList : public QWidget
{
    Q_OBJECT
public:
    KeyBoard* key_widget;
    GradeWidget* grade_widget;
    RegardTable* regard;
public:
    explicit TextList(QWidget *parent = 0);
    ~TextList();

private:
    Ui::TextList *ui;
};

#endif // TEXTLIST_H
