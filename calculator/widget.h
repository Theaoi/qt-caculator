#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

signals:
    void calchangewindow();

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QString labeltxt;   //label 的文本
    QString linetxt;    //编辑框的文本内容
    void help();
    void about();
    void input(QString word, QLineEdit* lineedit, QLabel* label);   //按下按钮时处理
    void compute(QLineEdit* lineedit, QLabel* label);               //按下 = 时处理计算

public slots:
    void calgetchange();
};

#endif // WIDGET_H
