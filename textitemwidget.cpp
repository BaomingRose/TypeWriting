#include "textitemwidget.h"
#include "ui_textitemwidget.h"
#include <QDebug>

TextItemWidget::TextItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextItemWidget)
{
    ui->setupUi(this);
}

TextItemWidget::~TextItemWidget()
{
    delete ui;
}

void TextItemWidget::on_pushButton_clicked()
{
    qDebug() << "点击";
}
