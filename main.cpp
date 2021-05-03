#include "keyboard.h"
#include "login.h"
#include <QApplication>
#include "textlist.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if 1
    KeyBoard w;
    w.show();
    w.init_text("./files/test.txt");

    Login l;
    l.show();
#endif

#if 1
    TextList* t = new TextList;
    t->show();
#endif


    return a.exec();
}
