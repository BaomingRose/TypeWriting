#include "textlist.h"
#include "ui_textlist.h"
#include "textitemwidget.h"

#include <QDebug>
#include <QDir>

TextList::TextList(QWidget *parent) :
    QWidget(parent),
    key_widget(nullptr),
    ui(new Ui::TextList)
{
    ui->setupUi(this);

    //遍历文件夹
    QDir dir("./files/");
    if(!dir.exists()) {
        qDebug() << "it is not true path";
        return ;
    }
    /* 设置过滤配置,只匹配文件 */
    dir.setFilter(QDir::Files);

    /* 返回目录中所有文件和目录的QFileInfo对象列表 */
    QFileInfoList file_list = dir.entryInfoList();
    foreach(const QFileInfo &fileInfo, file_list) {
        QString fileName = fileInfo.fileName(); /* 文件名字 */
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget, 0);
        item->setSizeHint(QSize(385,42));
        QWidget* w = new TextItemWidget(fileName, ui->listWidget);
        w->show();
        ui->listWidget->setItemWidget(item, w);

        //qDebug() << fileName;
    }
}

TextList::~TextList()
{
    delete ui;
}
