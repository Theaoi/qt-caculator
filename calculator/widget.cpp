#include "widget.h"
#include "backans.h"
#include <QPushButton>
#include <QGridLayout>
#include <QMenu>
#include <QMessageBox>
#include <QToolBar>
#include <QToolButton>

void Widget::help()
{
    QMessageBox::question(this,tr("Help"), tr("本程序支持含括号，求余在内的四则连续运算，以及贷款计算。\n支持复数，小数运算，并且精度为小数点后五位。\n支持简单的错误性检验\n'CE'清空 'Del' 后退 'More' 切换至贷款计算"),
                          QMessageBox::Yes,QMessageBox::Yes);
}
void Widget::about()
{
    QMessageBox::question(this,tr("About"), "作者：蒲苏\n博客：https://www.cnblogs.com/Trump-He/\nQQ：1643460951\n欢迎交流，转载请保留源地址。\n\nAuthor: Trump He\nBlog: https://www.cnblogs.com/Trump-He/\nQQ: 1643460951\nWelcome to chat, reprint please keep the source address.",
                          QMessageBox::Yes,QMessageBox::Yes);
}
void Widget::calgetchange()
{
    this->show();
}
void Widget::compute(QLineEdit* lineedit, QLabel* label)
{
    string tmpstr = linetxt.toStdString();
    QString ans = QString::number(backans::result(tmpstr), 10, 5);          //计算式子并输出结果
    lineedit->setText(ans);
    labeltxt = linetxt;
    label->setText(labeltxt);
    linetxt = ans;
}
void Widget::input(QString word, QLineEdit* lineedit, QLabel* label)
{
    if(word == "="){
        if(linetxt == "")   label->setText("请输入要计算的式子...");         //处理事件
        else    compute(lineedit, label);
    }
    else if (word == "More") {
        this->hide();
        emit calchangewindow();
    }
    else if (word == "CE") {
        linetxt = "";
        labeltxt = "";
        label->setText("");
        lineedit->setText(linetxt);
    }
    else if (word == "Del") {
        QString tmp = "";
        for (int i=0; i < linetxt.length()-1; i++)
            tmp += linetxt[i];
        linetxt = tmp;
        lineedit->setText(linetxt);
    }
    else {
        linetxt+=word;
        lineedit->setText(linetxt);
    }
}

Widget::Widget(QWidget *parent)
    : QWidget(parent),labeltxt(""),linetxt("")
{
    setFixedSize(400,450);
    setWindowIcon(QIcon(":/icon.png"));

    QLineEdit* lineedit = new QLineEdit(this);
    lineedit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QLabel* label = new QLabel(this);
    label->setText("");
    lineedit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QString btnstr[22] = {"(", ")", "%", "CE", "Del",
                        "7", "8", "9", "+", "-",
                        "4", "5", "6", "*", "/",
                        "1", "2", "3", "More", "=",
                        "0", "."
                       };
    auto that = this;
    QPushButton* btn[22];
    for(int i=0; i<22; i++){
        btn[i] = new QPushButton(that);
        btn[i]->setText(btnstr[i]);
        btn[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(btn[i],&QPushButton::clicked,that,[=](){
            that->input(btnstr[i], lineedit, label);
        });
    }
    btn[4]->setStyleSheet("color:red;");
    btn[18]->setStyleSheet("color:yellow;");
    int cyellow[9] = {0,1,2,3,8,9,13,14};
    for(int i=0; i<9; i++)  btn[cyellow[i]]->setStyleSheet("color:#38d6d5;");
    lineedit->setStyleSheet("color:#333;font-size:21px;font-weight:bolder;border:1px dashed #f1f1f1;border-radius:5px;text-align:right;");
    label->setStyleSheet("font-size:12px;color:grey;border-bottom:1px solid #f1f1f1;border-radius:5px;text-align:right;");
    lineedit->setAlignment( Qt::AlignRight);
    label->setAlignment( Qt::AlignRight);
    setStyleSheet("QPushButton {font-size:20px;font-weight:bold;color:ligrhtgrey;background-color: rgba(255, 255, 255, 0%);border:1px solid grey;border-radius:5px;} QPushButton:hover, QLabel:hover {font-size:25px;} Widget {background:qlineargradient(spread:pad,y1:1,y2:0,stop:0 #79f4f3,stop:1 #f8fefe);}");
    setWindowTitle("Calculator");
    QGridLayout* computelayout = new QGridLayout(this);
    computelayout->addWidget(label, 0, 0, 1, 5);
    computelayout->addWidget(lineedit, 1, 0, 1, 5);
    computelayout->addWidget(btn[0], 2, 0, 1, 1);
    computelayout->addWidget(btn[1], 2, 1, 1, 1);
    computelayout->addWidget(btn[2], 2, 2, 1, 1);
    computelayout->addWidget(btn[3], 2, 3, 1, 1);
    computelayout->addWidget(btn[4], 2, 4, 1, 1);
    computelayout->addWidget(btn[5], 3, 0, 1, 1);
    computelayout->addWidget(btn[6], 3, 1, 1, 1);
    computelayout->addWidget(btn[7], 3, 2, 1, 1);
    computelayout->addWidget(btn[8], 3, 3, 1, 1);
    computelayout->addWidget(btn[9], 3, 4, 1, 1);
    computelayout->addWidget(btn[10], 4, 0, 1, 1);
    computelayout->addWidget(btn[11], 4, 1, 1, 1);
    computelayout->addWidget(btn[12], 4, 2, 1, 1);
    computelayout->addWidget(btn[13], 4, 3, 1, 1);
    computelayout->addWidget(btn[14], 4, 4, 1, 1);
    computelayout->addWidget(btn[15], 5, 0, 1, 1);
    computelayout->addWidget(btn[16], 5, 1, 1, 1);
    computelayout->addWidget(btn[17], 5, 2, 1, 1);
    computelayout->addWidget(btn[18], 5, 3, 2, 1);
    computelayout->addWidget(btn[19], 5, 4, 2, 1);
    computelayout->addWidget(btn[20], 6, 0, 1, 2);
    computelayout->addWidget(btn[21], 6, 2, 1, 1);

    QToolButton* toolButton = new QToolButton(this);
    toolButton->setText("Help and About");
    toolButton->setPopupMode(QToolButton::MenuButtonPopup);
    QMenu * m = new QMenu(this);
    QAction *a1 = m->addAction("help");
    QAction *a2 = m->addAction("about");
    connect(a1,&QAction::triggered,this,&Widget::help);
    connect(a2,&QAction::triggered,this,&Widget::about);
    toolButton->setMenu(m);
    QToolBar * toolBar = new QToolBar(this);
    toolBar->addWidget(toolButton);
    computelayout->addWidget(toolBar,7,0,1,3);
}

Widget::~Widget()
{

}
