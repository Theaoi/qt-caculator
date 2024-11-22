#ifndef MORTGAGE_H
#define MORTGAGE_H

#include <QWidget>

class mortgage : public QWidget
{
    Q_OBJECT

signals:
    void morchangewindow();

public:
    mortgage(QWidget *parent = 0);
    ~mortgage();


public  slots:
    void morgetchange();   //接收来自计算器界面的信号
    void exitslot();       //隐藏窗口并释放切换窗口信号
};

#endif // MORTGAGE_H
