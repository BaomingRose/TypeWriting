#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QNetworkAccessManager>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_login_btn_clicked();

    void replyFinished1(QNetworkReply*);   //收到登录请求后调用
    void replyFinished2(QNetworkReply*);   //收到注册请求后调用

    void on_not_online_clicked();

private:
    Ui::Login *ui;

    QNetworkAccessManager* log_mag;          //管理登录请求
    QNetworkAccessManager* register_mag;     //管理注册请求
};

#endif // LOGIN_H
