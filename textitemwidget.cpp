#include "textitemwidget.h"
#include "ui_textitemwidget.h"
#include <QDebug>
#include <QFile>
#include <QVector>
#include "textlist.h"
#include "regardtable.h"

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
    if (tl->regard != nullptr) {
        tl->regard->close();
        tl->regard = nullptr;
    }

    QString file_path = "./records/" + ui->label->text() + ".regard";
    RegardTable* rt = new RegardTable;
    tl->regard = rt;
    rt->setWindowTitle(ui->label->text() + "记录排行");
    rt->setWindowFlags(Qt::WindowStaysOnTopHint);

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

    rt->set_lable(ui->label->text());
    rt->set_table(grades);
    rt->show();
}
