#include "login.h"
#include "ui_login.h"

#include <QDebug>
#include <QTextCodec>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>


Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->warning->hide();

    log_mag = new QNetworkAccessManager(this);
    register_mag = new QNetworkAccessManager(this);

    connect(log_mag, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished1(QNetworkReply*)));
    connect(register_mag, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished1(QNetworkReply*)));

}

Login::~Login()
{
    delete ui;
}

void Login::on_login_btn_clicked()
{
    QString id = ui->log_id->text();
    QString password = ui->log_password->text();

    /*
     * 对两种数值的检查
     */

    //构造登录请求
    QString url = "http://127.0.0.1:3000/log?id=" + id + "&password=" + password;
    log_mag->get(QNetworkRequest(QUrl(url)));
}

void Login::replyFinished1(QNetworkReply *reply) {
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString all = codec->toUnicode(reply->readAll());
    qDebug() << all;

    if (all == "true") {
        this->ui->warning->hide();
        this->close();
    } else {
        this->ui->warning->show();
    }
}

void Login::replyFinished2(QNetworkReply *reply) {

}

void Login::on_not_online_clicked()
{

    this->close();
}
