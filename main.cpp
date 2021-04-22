#include "keyboard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KeyBoard w;
    w.show();

    return a.exec();
}
