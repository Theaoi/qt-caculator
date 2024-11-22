#include "mortgage.h"
#include <QGroupBox>
#include <QRadioButton>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QLayout>
#include <QPushButton>
#include <math.h>

void mortgage::morgetchange()
{
    this->show();
}
void mortgage::exitslot()
{
    this->hide();
    emit morchangewindow();
}
mortgage::mortgage(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(400,450);
    setWindowIcon(QIcon(":/icon.png"));  //窗口初始化及布局
    setWindowTitle("Mortgage");

    QGroupBox* mygroup = new QGroupBox(this);
    QLabel* grouplab = new QLabel(mygroup);
    grouplab->setText("还款方式：");
    QRadioButton* frabtn = new QRadioButton(mygroup);
    frabtn->setText("等额本息");
    frabtn->setChecked(true);
    QRadioButton* srabtn = new QRadioButton(mygroup);
    srabtn->setText("等额本金");
    srabtn->setChecked(false);
    QHBoxLayout* hlayout = new QHBoxLayout(mygroup);
    mygroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    grouplab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    frabtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    srabtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    hlayout->addWidget(grouplab);
    hlayout->addWidget(frabtn);
    hlayout->addWidget(srabtn);

    QLabel* labeltip[6];
    QLineEdit* linebox[6];
    QString titletxt[6] = {"贷款年限（年）：","贷款金额（万元）：","贷款利率（年,%）：","月均还款（元）：","利息总额（元）：","还款总额（元）："};
    for(int i=0; i<6; i++){
        labeltip[i] = new QLabel(this);
        labeltip[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        labeltip[i]->setText(titletxt[i]);
        linebox[i] = new QLineEdit(this);
        linebox[i]->setText("0");
        linebox[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
    QPushButton* computebtn = new QPushButton(this);
    computebtn->setText("计算");
    QPushButton* recomputebtn = new QPushButton(this);
    recomputebtn->setText("重新计算");
    QPushButton* exitbtn = new QPushButton(this);
    exitbtn->setText("返回");
    QGridLayout* mortgrid = new QGridLayout(this);
    computebtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    recomputebtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    exitbtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mortgrid->addWidget(mygroup, 0, 0, 1, 5);
    mortgrid->addWidget(labeltip[0], 1, 0, 1, 2);
    mortgrid->addWidget(linebox[0], 1, 2, 1, 3);
    mortgrid->addWidget(labeltip[1], 2, 0, 1, 2);
    mortgrid->addWidget(linebox[1], 2, 2, 1, 3);
    mortgrid->addWidget(labeltip[2], 3, 0, 1, 2);
    mortgrid->addWidget(linebox[2], 3, 2, 1, 3);
    mortgrid->addWidget(exitbtn, 4, 0, 1, 1);
    mortgrid->addWidget(computebtn, 4, 1, 1, 2);
    mortgrid->addWidget(recomputebtn, 4, 3, 1, 2);
    mortgrid->addWidget(labeltip[3], 5, 0, 1, 2);
    mortgrid->addWidget(linebox[3], 5, 2, 1, 3);
    mortgrid->addWidget(labeltip[4], 6, 0, 1, 2);
    mortgrid->addWidget(linebox[4], 6, 2, 1, 3);
    mortgrid->addWidget(labeltip[5], 7, 0, 1, 2);
    mortgrid->addWidget(linebox[5], 7, 2, 1, 3);

    setStyleSheet("QPushButton {font-size:20px;font-weight:bold;background-color: rgba(255, 255, 255, 0%);border:1px solid grey;border-radius:5px;} QPushButton:hover, QLabel:hover {font-size:25px;} mortgage {background:qlineargradient(spread:pad,y1:1,y2:0,stop:0 #79f4f3,stop:1 #f8fefe);}");
    exitbtn->setStyleSheet("color:red;");

    connect(computebtn,&QPushButton::clicked,this,[=](){
        double yearM = linebox[0]->text().toDouble() * 12;
        double money = linebox[1]->text().toDouble() * 10000;
        double rate = linebox[2]->text().toDouble() / 1200;
        double moHuan, moLi, moZli;
        if(yearM && money && rate){
            if(frabtn->isChecked()){
                moHuan = money * rate * pow(1 + rate, yearM) / (pow(1 + rate, yearM) - 1);
                moLi = moHuan * yearM - money;
                moZli = moHuan * yearM;
            }
            else{
                moHuan = (money / yearM) + (money - money) * rate;
                moLi = (money / yearM + money * rate + money / yearM * (1 + rate)) / 2 * yearM - money;
                moZli = (money / yearM + money * rate + money / yearM * (1 + rate)) / 2 * yearM;
            }
            linebox[3]->setText(QString::number(moHuan, 10, 5));
            linebox[4]->setText(QString::number(moLi, 10, 5));
            linebox[5]->setText(QString::number(moZli, 10, 5));
        }
        else {
            linebox[3]->setText("没有填完整哦");
            linebox[4]->setText("没有填完整哦");
            linebox[5]->setText("没有填完整哦");
        }
    });
    connect(recomputebtn,&QPushButton::clicked,this,[=](){
        linebox[0]->setText("0");
        linebox[1]->setText("0");
        linebox[2]->setText("0");
        linebox[3]->setText("0");
        linebox[4]->setText("0");
        linebox[5]->setText("0");
    });
    connect(exitbtn,&QPushButton::clicked,this,&mortgage::exitslot);
}

mortgage::~mortgage()
{

}


