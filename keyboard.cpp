#include "keyboard.h"
#include "ui_keyboard.h"
#include <qDebug>
#include <qfile.h>
#include <QPushButton>
#include <qpushbutton.h>
#include <qpalette.h>
#include <QPalette>
#include <qapplication.h>
#include <qvector.h>
#include <qalgorithms.h>
#include "textlist.h"
#include "ui_gradewidget.h"

KeyBoard::KeyBoard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KeyBoard),
    cur_charactors(0),
    correct_num(0),
    error_num(0),
    cur_time(0),
    is_start(false),
    cur_handled_pos(-1),
    is_handling(false),
    is_backspace(false),
    userid(-1),
    red_btn(nullptr),
    cur_show_str("When you are a child, you are good."),
    file(nullptr),
    file_path("./files/test.txt")
{
#if 0
    //路径为生成的文件路径
    QString textpath = "./files/test.txt";
    QFile file(textpath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "can't open ：" + textpath;
    }

    QString Content = QString(file.readLine());         //获取文件文本字符串
    Content = Content.simplified();                     //去掉\r\n，并用空格代替
    qDebug() << Content;

    QString str = QString(file.readLine());
    qDebug() << str;

    str = QString(file.readLine());
    qDebug() << str;
#endif

    //需要打开文件计算当前总字符量
    total_charactors = 100;

    /*定时器初始化*/
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerHandleSlot()));
    //debug，1秒一定时
    //timer->start(1000);

    ui->setupUi(this);

    this->setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(), this->height());

#if 0
    /*调式按钮颜色，此代码不再需要
    QPushButton* pushButton = ui->pushButton_W;
    //pushButton->setStyleSheet("background-color:yellow");
    set_btn_color(pushButton, 2);
    set_btn_color(pushButton, 0);
    //set_btn_color(pushButton);
    */
#endif

    ui->view1->setFocus();
    ui->view1->installEventFilter(this);
}

KeyBoard::~KeyBoard()
{
    delete ui;
}

//设置字符背景颜色
//n为倒数第n个字符
void KeyBoard::set_char_background(unsigned int pos, QString color, int n)
{
    if(pos <= 0)
        return;

    QTextEdit* tempview = ui->view1;

    QTextCursor cursor = tempview->textCursor();
    //行首
    cursor.movePosition( QTextCursor::StartOfLine );
    //向右移动到Pos-1,即待修改的字符左边
    //cursor.movePosition( QTextCursor::Right, QTextCursor::MoveAnchor, pos-1);
    cursor.movePosition( QTextCursor::Right, QTextCursor::MoveAnchor, pos - n);
    //选中这个字符
    cursor.movePosition( QTextCursor::NextCharacter, QTextCursor::KeepAnchor );
    // added,使选中生效,必须有这句
    tempview->setTextCursor(cursor);

    //修改前字符格式
    QTextCharFormat defcharfmt = tempview->currentCharFormat();
    //新增字符格式
    QTextCharFormat newcharfmt = defcharfmt;
    //颜色
    newcharfmt.setBackground(QColor(color));
    tempview->setCurrentCharFormat(newcharfmt);

    //加上这句是为了去除光标selected,这时光标在字符左边
    cursor.movePosition(QTextCursor::PreviousCharacter);
    //这时光标在行尾
    cursor.movePosition(QTextCursor::EndOfLine);
    //added,使选中生效,必须有这句
    tempview->setTextCursor(cursor);
}

//设置字符前景色，即字符颜色
void KeyBoard::set_char_foreground(unsigned int pos, QString color, int n)
{
    if(pos <= 0)return ;

    QTextEdit * tempview = ui->view1;

    QTextCursor cursor = tempview->textCursor();
    //行首
    cursor.movePosition( QTextCursor::StartOfLine );
    //向右移动到Pos-1,即待修改的字符左边
    cursor.movePosition( QTextCursor::Right, QTextCursor::MoveAnchor, pos - n);
    //选中这个字符
    cursor.movePosition( QTextCursor::NextCharacter, QTextCursor::KeepAnchor );
    //added,使选中生效,必须有这句
    tempview->setTextCursor(cursor);

    //修改前字符格式
    QTextCharFormat defcharfmt = tempview->currentCharFormat();
    //新增字符格式
    QTextCharFormat newcharfmt = defcharfmt;
    //字符颜色
    newcharfmt.setForeground(QColor(color));

    tempview->setCurrentCharFormat(newcharfmt);

    //加上这句是为了去除光标selected，这时光标在字符左边
    cursor.movePosition(QTextCursor::PreviousCharacter);
   //这时光标在行尾
    cursor.movePosition(QTextCursor::EndOfLine);
    //added,使选中生效,必须有这句
    tempview->setTextCursor(cursor);
}


QPushButton* KeyBoard::get_button(char ch) {
    switch(ch) {
    case '1':
        return ui->pushButton_1;
    case '2':
        return ui->pushButton_2;
    case '3':
        return ui->pushButton_3;
    case '4':
        return ui->pushButton_4;
    case '5':
        return ui->pushButton_5;
    case '6':
        return ui->pushButton_6;
    case '7':
        return ui->pushButton_7;
    case '8':
        return ui->pushButton_8;
    case '9':
        return ui->pushButton_9;
    case '0':
        return ui->pushButton_0;
    case 'a':
        return ui->pushButton_A;
    case 'b':
        return ui->pushButton_B;
    case 'c':
        return ui->pushButton_C;
    case 'd':
        return ui->pushButton_D;
    case 'e':
        return ui->pushButton_E;
    case 'f':
        return ui->pushButton_F;
    case 'g':
        return ui->pushButton_G;
    case 'h':
        return ui->pushButton_H;
    case 'i':
        return ui->pushButton_I;
    case 'j':
        return ui->pushButton_J;
    case 'k':
        return ui->pushButton_K;
    case 'l':
        return ui->pushButton_L;
    case 'm':
        return ui->pushButton_M;
    case 'n':
        return ui->pushButton_N;
    case 'o':
        return ui->pushButton_O;
    case 'p':
        return ui->pushButton_P;
    case 'q':
        return ui->pushButton_Q;
    case 'r':
        return ui->pushButton_R;
    case 's':
        return ui->pushButton_S;
    case 't':
        return ui->pushButton_T;
    case 'u':
        return ui->pushButton_U;
    case 'v':
        return ui->pushButton_V;
    case 'w':
        return ui->pushButton_W;
    case 'x':
        return ui->pushButton_X;
    case 'y':
        return ui->pushButton_Y;
    case 'z':
        return ui->pushButton_Z;
    case ';':
        return ui->pushButton_semi;
    case ':':
        return ui->pushButton_semi;
    case ' ':
        return ui->pushButton_Space;
    case '!':
        return ui->pushButton_1;
    case '@':
        return ui->pushButton_2;
    case '#':
        return ui->pushButton_3;
    case '$':
        return ui->pushButton_4;
    case '%':
        return ui->pushButton_5;
    case '^':
        return ui->pushButton_6;
    case '&':
        return ui->pushButton_7;
    case '*':
        return ui->pushButton_8;
    case '(':
        return ui->pushButton_9;
    case ')':
        return ui->pushButton_0;
    case '-':
        return ui->pushButton_sub;
    case '_':
        return ui->pushButton_sub;
    case '+':
        return ui->pushButton_equal;
    case '=':
        return ui->pushButton_equal;
    case '[':
        return ui->pushButton_left;
    case '{':
        return ui->pushButton_left;
    case ']':
        return ui->pushButton_right;
    case '}':
        return ui->pushButton_right;
    case '\\':
        return ui->pushButton_rev;
    case '|':
        return ui->pushButton_rev;
    case ',':
        return ui->pushButton_comma;
    case '<':
        return ui->pushButton_comma;
    case '.':
        return ui->pushButton_full;
    case '>':
        return ui->pushButton_full;
    case '\'':
        return ui->pushButton_quo;
    case '"':
        return ui->pushButton_quo;
    case '/':
        return ui->pushButton_div;
    case '?':
        return ui->pushButton_div;
    case 127:
        return ui->pushButton_Shift;
    case 126:
        return ui->pushButton_Shift_2;
    }
    return nullptr;
}

void KeyBoard::set_btn_color(QPushButton* button, int choice) {
    //默认颜色为：background-color: rgb(219, 207, 230);
    //background-color: rgb(85, 0, 0);//棕色
    if (choice == 0) {
        button->setStyleSheet("background-color: rgb(85, 0, 0);");
    } else if (choice == 1) {
        button->setStyleSheet("background-color: rgb(85, 255, 0);");
    } else if (choice == 2) {
        button->setStyleSheet("background-color: rgb(255, 0, 0);");
    }
}


//=========================文本导入相关================================
/*初始化文本*/
void KeyBoard::init_text(QString textpath = "./files/test.txt") {
    file_path = textpath.mid(8);
    file = new QFile(textpath);
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "can't open ：" + textpath;
    }
    get_new_line();
}

/*从文件获取新一行，并给模板框设置字符串*/
void KeyBoard::get_new_line() {
    if (file->atEnd()) {
        timer->stop();

        /*结束处理，弹出成绩*/
        TextList* tl = (TextList*)this->parent();
        tl->grade_widget = new GradeWidget(this);
        tl->grade_widget->setWindowFlags(tl->grade_widget->windowFlags() |Qt::Dialog);
//        unsigned minute = cur_time / 60;
//        unsigned second = cur_time % 60;

        unsigned speed = correct_num * 60 / cur_time;
        tl->grade_widget->ui->label->setText("本次成绩为：" + QString::number(speed) + "字/分钟");

        tl->grade_widget->show();

        /*将成绩更新至记录中*/
        update_grade(speed);

        file->close();
        return;
    }
    cur_show_str = file->read(LINE_NUMBER);

    ui->view0->setText(cur_show_str);
    ui->view1->setText("");
    ui->view1->setFocus();

    /*亮出第一个按钮*/
    QPushButton* btn = get_button(cur_show_str[0].toLower().toLatin1());
    if (btn) {
        greens.push_back(btn);
        set_btn_color(btn, 1);
    }

    cur_handled_pos = -1;
}

/*将成绩更新*/
void KeyBoard::update_grade(unsigned new_grade) {
    qDebug() << "new_grade:" << new_grade;
    QString cur_file_path = "./records/" + file_path + ".regard";
    QFile* f = new QFile(cur_file_path);
    if (!f->open(QIODevice::ReadOnly)) {
        qDebug() << "can't open ：" + cur_file_path;
    }
    QDataStream stream_read(f);
    QVector<unsigned> grades;
    while (!stream_read.atEnd()) {
        unsigned cur;
        stream_read >> cur;
        //stream_read.readRawData((char*)&cur, sizeof(cur));
        grades.append(cur);
    }
    f->close();

    grades.append(new_grade);
    qSort(grades.begin(), grades.end(), [](const unsigned& a, const unsigned& b){return a > b;});
    if (grades.size() > 10) {
        grades.pop_back();
    }

    //debug
    for (int i = 0; i < grades.size(); ++i) {
        qDebug() << grades[i];
    }

    QFile* f2 = new QFile(cur_file_path);
    if (!f2->open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "can't open ：" + cur_file_path;
    }
    QDataStream stream_write(f2);
    for (int i = 0; i < grades.size(); ++i) {
        unsigned cur = grades[i];
        stream_write << cur;
        //stream_write.writeRawData((char*)cur, sizeof(cur));
    }
    f2->close();
}

//=========================以下为槽函数的定义================================
/*定时器到时槽函数*/
void KeyBoard::timerHandleSlot() {
    //qDebug() << "定时器打印";
    cur_time += 3;
    //计算打字速度
    unsigned long speed = correct_num * 60 / cur_time;

    //给界面更新数据(打字速度)
    ui->lineEdit3->setText(QString::number(speed));
}

/*用户输入框槽函数：防止指针被前移*/
void KeyBoard::on_view1_cursorPositionChanged()
{
    //qDebug() << "cur position changed";
    ui->view1->moveCursor(QTextCursor::End);
}

/*用户输入框槽函数：本本改变*/
void KeyBoard::on_view1_textChanged()
{
    /*特别注意的点：因为在做字符样式的修改也会触发到这个槽函数，就会形成一个递归*/
    if (is_handling) {
        return;
    }
    is_handling = true;

    //只要文本改变，按钮就需要重新改变
    /*取消之前的绿色按钮*/
    for (auto& e : greens) {
        set_btn_color(e, 0);
    }
    greens.clear();
    /*取消之前的红色按钮*/
    if (red_btn) {
        set_btn_color(red_btn, 0);
        red_btn = nullptr;
    }

    /*如果是backspace事件*/
    if (is_backspace) {
        /*核心处理回删*/
        --cur_charactors;

        QString cur_str = ui->view1->toPlainText();
        //判断最后一个被删除是正确还是错误

        /*此两行代码为作废代码*/
        //qDebug() << cur_str.mid(0, cur_str.size() - 1);
        //ui->view1->setText(cur_str.mid(0, cur_str.size() - 1));

        bool is_last_true = cur_str[cur_handled_pos] == cur_show_str[cur_handled_pos];
        if (is_last_true) {
            --correct_num;
            ui->lineEdit0->setText(QString::number(correct_num));
        } else {
            --error_num;
            ui->lineEdit1->setText(QString::number(error_num));
        }

        /*找到光标操作删除最后一个字符*/
        QTextCursor cursor = ui->view1->textCursor();
        cursor.movePosition(QTextCursor::End);
        cursor.deletePreviousChar();
        ui->view1->setFocus();

        --cur_handled_pos;

        /*将下一个字符置为绿色*/
        char next = cur_show_str[cur_handled_pos + 1].toLatin1();
        if (next == '!' || next == '@' || next == '#' || next == '$' || next == '%' || next == '^' || next == 'Q' || next == 'W' || next == 'E' || next == 'R' || next == 'T'
                || next == 'A' || next == 'S' || next == 'D' || next == 'F' || next == 'G' || next == 'Z' || next == 'X' || next == 'C' || next == 'V' || next == 'B') {
            greens.push_back(ui->pushButton_Shift_2);
            set_btn_color(ui->pushButton_Shift_2, 1);
        } else if (next == '&' || next == '*' || next == '(' || next == ')' || next == '_' || next == '+' || next == '{' || next == '}' || next == '|' || next == ':' || next == '"' || next == '<' || next == '>' || next == '?' ||
                   next == 'Y' || next == 'U' || next == 'I' || next == 'O' || next == 'P' || next == 'J' || next == 'K' || next == 'L' || next == 'N' || next == 'M') {
            greens.push_back(ui->pushButton_Shift);
            set_btn_color(ui->pushButton_Shift, 1);
        }
        QPushButton* new_green = get_button(cur_show_str[cur_handled_pos + 1].toLower().toLatin1());
        if (new_green) {
            greens.push_back(new_green);
            set_btn_color(new_green, 1);
        }

        is_backspace = false;
        is_handling = false;
        return;
    }

    //如果未开始，则开始计时
    if (!is_start) {
        is_start = true;
        timer->start(3000);
    }


    //获取到当前文本位置，下一个字符的按钮显示(上一个绿色和红色字符颜色取消，并显示下一个绿色和红色字符)
    QString str = ui->view1->toPlainText();

    //接收的字符串
    int len = str.length();
    //num长度计算错误，还需要减1
    int num = len - cur_handled_pos - 1;
    /*分别获取接收和对比字符串*/
    QString input_str = str.mid(cur_handled_pos + 1, num);
    //QString pattern_str = cur_show_str.mid(cur_handled_pos + 1, num);

    /*处理cur_handled_pos开始到结束的字符*/
    for (int i = 0; i < num; ++i) {
        if (input_str[i] == cur_show_str[cur_handled_pos + 1 + i]) {
            //正确前景色白，倒数第n个字符
            set_char_background(len, "#FFFFFF", num - i);
            //正确背景色灰
            set_char_foreground(len, "#ABABAB", num - i);

            if (red_btn) {
                set_btn_color(red_btn, 0);
            }

            ++correct_num;
        } else {
            //错误，前景色黑
            set_char_background(len, "#0D0D0D", num - i);
            //错误，背景色黄色
            set_char_foreground(len, "#EEEE00", num - i);
            QApplication::beep();
            ++error_num;

            /*做最后按钮的改变*/
            //计算len-1位置是否正确，不正确则按钮置红
            red_btn = get_button(input_str[i].toLower().toLatin1());
            if (red_btn) {
                set_btn_color(red_btn, 2);
            }
        }
    }

    /*进度更新，并设置几个窗口数据*/
    cur_charactors += num;

    /*更新处理位置*/
    cur_handled_pos = len - 1;
    ui->lineEdit0->setText(QString::number(correct_num));
    ui->lineEdit1->setText(QString::number(error_num));
    ui->lineEdit2->setText(QString::number((double)correct_num / (double)cur_charactors * 100).mid(0, 4));
    ui->lineEdit4->setText(QString::number((double)cur_charactors / (double)total_charactors * 100).mid(0, 4));

    /*如果到输入结尾了，则接收下一行，并将输入框置空*/
    if (str.size() == cur_show_str.size()) {
        get_new_line();
        is_handling = false;
        return;
    }

    /*将下一个字符的按钮置绿*/
    char next = cur_show_str[cur_handled_pos + 1].toLatin1();
    if (next == '!' || next == '@' || next == '#' || next == '$' || next == '%' || next == '^' || next == 'Q' || next == 'W' || next == 'E' || next == 'R' || next == 'T'
            || next == 'A' || next == 'S' || next == 'D' || next == 'F' || next == 'G' || next == 'Z' || next == 'X' || next == 'C' || next == 'V' || next == 'B') {
        greens.push_back(ui->pushButton_Shift_2);
        set_btn_color(ui->pushButton_Shift_2, 1);
    } else if (next == '&' || next == '*' || next == '(' || next == ')' || next == '_' || next == '+' || next == '{' || next == '}' || next == '|' || next == ':' || next == '"' || next == '<' || next == '>' || next == '?' ||
               next == 'Y' || next == 'U' || next == 'I' || next == 'O' || next == 'P' || next == 'J' || next == 'K' || next == 'L' || next == 'N' || next == 'M') {
        greens.push_back(ui->pushButton_Shift);
        set_btn_color(ui->pushButton_Shift, 1);
    }
    QPushButton* new_green = get_button(cur_show_str[cur_handled_pos + 1].toLower().toLatin1());
    if (new_green) {
        greens.push_back(new_green);
        set_btn_color(new_green, 1);
    }

    //最后要将处理中标志置回
    is_handling = false;
}

//事件过滤器：监听文本框聚焦情况
bool KeyBoard::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->view1){                          //首先判断控件(这里指 VIEW1)
        if (event->type()==QEvent::FocusIn)             //然后再判断控件的具体事件 (这里指获得焦点事件)
        {
        }
        if (event->type()==QEvent::FocusOut)            // 这里指 view1 控件的失去焦点事件
        {
        }
    }

    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *e = static_cast<QKeyEvent*>(event);
        switch (e->key())
        {//如果采用keyPressEvent在文本框中只能检测到key_escape;加上与不加上return true;有很大区别
         //没加上会是实际效果，加上了就不会处理。
        /*  关键内容*/
        case Qt::Key_Backspace  : {//过滤器监听到回删按键，然后再发送文本改变信号
            //qDebug() << "回删事件";
            if (ui->view1->toPlainText().size() == 0) {
                return true;
            }
            is_backspace = true;
            emit on_view1_textChanged();
            return true;                        //必须有return ture否则backspace会产生效果。
        }

         case Qt::Key_Return     : return true;
         case Qt::Key_Enter      : return true;
         case Qt::Key_Delete     : return true;
         case Qt::Key_Tab        : return true;
         case Qt::Key_Escape     : {//"Esc"按键
            QApplication::beep ();
            qDebug() << "Key_Escape";
                return true;
            }
        }
    }
    return QWidget::eventFilter(watched, event);         // 最后将事件交给上层对话框
}

void KeyBoard::closeEvent(QCloseEvent *event) {
    event->accept();
    TextList* tl = (TextList*)this->parent();
    tl->show();
}

