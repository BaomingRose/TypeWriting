#ifndef TEXTLIST_H
#define TEXTLIST_H

#include <QWidget>

namespace Ui {
class TextList;
}

class TextList : public QWidget
{
    Q_OBJECT

public:
    explicit TextList(QWidget *parent = 0);
    ~TextList();

private:
    Ui::TextList *ui;
};

#endif // TEXTLIST_H
