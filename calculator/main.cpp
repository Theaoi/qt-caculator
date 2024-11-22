#include "widget.h"
#include "mortgage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    mortgage m;
    m.hide();
    w.show();
    QObject::connect(&w, &Widget::calchangewindow, &m, &mortgage::morgetchange);    //链接两个窗口
    QObject::connect(&m, &mortgage::morchangewindow, &w, &Widget::calgetchange);

    return a.exec();
}
