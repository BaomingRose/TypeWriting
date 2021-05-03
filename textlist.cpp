#include "textlist.h"
#include "ui_textlist.h"
#include "textitemwidget.h"

TextList::TextList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextList)
{
    ui->setupUi(this);

    //debug
    for (int i = 0; i < 20; ++i) {
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget, 0);
        item->setSizeHint(QSize(385,42));
        QWidget* w = new TextItemWidget(ui->listWidget);
        w->show();
        ui->listWidget->setItemWidget(item, w);
    }
}

TextList::~TextList()
{
    delete ui;
}
