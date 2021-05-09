#include "regardtable.h"
#include "ui_regardtable.h"

RegardTable::RegardTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegardTable)
{
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnWidth(0, 200);
    this->setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
}

RegardTable::~RegardTable()
{
    delete ui;
}

void RegardTable::set_table(const QVector<unsigned>& v) {
    ui->tableWidget->setRowCount(v.size());
    for (int i = 0; i < v.size(); ++i) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(v[i]) + "字/分钟"));
    }
}

void RegardTable::set_lable(const QString str) {
    ui->label->setText(str);
}
