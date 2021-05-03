#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QMainWindow>
#include <QTimer>
#include <qevent.h>
#include <qpushbutton.h>
#include <qvector.h>

#define LINE_NUMBER 51                      //一行能够显示的字符数

namespace Ui {
class KeyBoard;
}

class KeyBoard : public QMainWindow
{
    Q_OBJECT

/*打字练习部分*/
private:
    /*==============================打字数据相关=====================================*/
    unsigned long total_charactors;   //文章总字符数量
    unsigned long cur_charactors;     //当前打字总数量
    unsigned long correct_num;        //当前正确量
    unsigned long error_num;          //当前错误量
    unsigned long cur_time;           //当前时间
    bool is_start;                    //表示是否开始打字
    QTimer* timer;                    //定时器
    //int debug = 0;

    QString cur_show_str;             //当前展示框内容
    int cur_handled_pos;    //当前已经处理过的位置
    bool is_handling;       //表示是否正在处理中，防止修改样式触发槽函数形成递归
    bool is_backspace;      //表示当前键盘是否为回删事件

    //用户相关
    int userid;

    /*============================按钮变色相关========================================*/
    /*变色按钮*/
    QPushButton* red_btn;
    QVector<QPushButton*> greens;

    /*核心：设置字符背景*/
    void set_char_background(unsigned int pos, QString color, int n);  //设置字符背景颜色
    void set_char_foreground(unsigned int pos, QString color, int n);  //设置字符颜色

    QPushButton* get_button(char ch);
    void set_btn_color(QPushButton* button, int choice);

    /*===============================文本导入相关====================================*/
    QFile* file;
public:
    void init_text(QString textpath);
    void get_new_line();

public:
    explicit KeyBoard(QWidget *parent = 0);
    ~KeyBoard();

private slots:
    void timerHandleSlot();

    void on_view1_cursorPositionChanged();

    void on_view1_textChanged();

    bool eventFilter(QObject *,QEvent *);  //事件过滤器来监听文本框聚焦情况

private:
    Ui::KeyBoard *ui;
};

#endif // KEYBOARD_H
