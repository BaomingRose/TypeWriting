#include "listtext.h"
#include "ui_listtext.h"

ListText::ListText(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListText)
{
    ui->setupUi(this);
}

ListText::~ListText()
{
    delete ui;
}
