#include "textitemwidget.h"
#include "ui_textitemwidget.h"
#include <QDebug>
#include "textlist.h"

TextItemWidget::TextItemWidget(QString text, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextItemWidget)
{
    ui->setupUi(this);
    ui->label->setText(text);
}

TextItemWidget::~TextItemWidget()
{
    delete ui;
}

void TextItemWidget::on_pushButton_clicked()
{
    TextList* tl = (TextList*)this->parent()->parent()->parent();
    if (tl->key_widget) {
        tl->key_widget->close();
        tl->key_widget = nullptr;
    }
    tl->key_widget = new KeyBoard(tl);
    tl->key_widget->show();
    tl->key_widget->init_text("./files/" + ui->label->text());

    tl->hide();
}
