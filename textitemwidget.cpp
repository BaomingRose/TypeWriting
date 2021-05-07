#include "textitemwidget.h"
#include "ui_textitemwidget.h"
#include <QDebug>
#include <QFile>
#include <QVector>
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

void TextItemWidget::on_pushButton_2_clicked()
{
    TextList* tl = (TextList*)this->parent()->parent()->parent();

    QString file_path = "./records/" + ui->label->text() + ".regard";

    QFile* f = new QFile(file_path);
    if (!f->open(QIODevice::ReadOnly)) {
        qDebug() << "can't open ：" + file_path;
    }
    QDataStream stream_read(f);
    QVector<unsigned> grades;
    while (!stream_read.atEnd()) {
        int cur;
        stream_read >> cur;
        //stream_read.readRawData((char*)&cur, sizeof(cur));
        grades.append(cur);
        qDebug() << cur;
    }
    f->close();

}
