#ifndef REGARDTABLE_H
#define REGARDTABLE_H

#include <QWidget>
#include <QVector>

namespace Ui {
class RegardTable;
}

class RegardTable : public QWidget
{
    Q_OBJECT

public:
    explicit RegardTable(QWidget *parent = 0);
    ~RegardTable();

    void set_table(const QVector<unsigned>& v);
    void set_lable(const QString str);

private:
    Ui::RegardTable *ui;
};

#endif // REGARDTABLE_H
