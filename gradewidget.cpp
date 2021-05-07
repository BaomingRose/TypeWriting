#include "gradewidget.h"
#include "ui_gradewidget.h"
#include "keyboard.h"
#include "textlist.h"

GradeWidget::GradeWidget(KeyBoard* kbp, QWidget *parent) :
    QWidget(parent),
    kb(kbp),
    ui(new Ui::GradeWidget)
{
    ui->setupUi(this);
}

GradeWidget::~GradeWidget()
{
    delete ui;
}

void GradeWidget::on_pushButton_clicked()
{
    this->close();
    kb->close();
}
