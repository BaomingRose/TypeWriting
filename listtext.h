#ifndef LISTTEXT_H
#define LISTTEXT_H

#include <QWidget>

namespace Ui {
class ListText;
}

class ListText : public QWidget
{
    Q_OBJECT

public:
    explicit ListText(QWidget *parent = 0);
    ~ListText();

private:
    Ui::ListText *ui;
};

#endif // LISTTEXT_H
