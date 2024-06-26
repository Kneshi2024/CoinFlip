#include "mycoin.h"
#include<QDebug>
#include<QLabel>
#include<QPixmap>

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{


//}
MyCoin::MyCoin(QString coinpath){
    this->CoinPath=coinpath;
    QPixmap pix;
    bool ret= pix.load(coinpath);
    if(!ret){
        qDebug()<<"图片加载失败";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());//控制窗口本身大小
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(QIcon(pix));
    this->setIconSize(pix.size());//控制窗口图标大小
    //初始化计时器对象
    timer1=new QTimer(this);
    timer2=new QTimer(this);
    //监听金币翻银币信号
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/Image/Coin000%1.png").arg(this->min++);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());//控制窗口本身大小
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(QIcon(pix));
        this->setIconSize(pix.size());//控制窗口图标大小
        if(this->min>this->max){
            this->min=1;
            this->isAnimation=false;
            timer1->stop();
        }
    });
    //监听银币反银币信号
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/Image/Coin000%1.png").arg(this->max--);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());//控制窗口本身大小
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(QIcon(pix));
        this->setIconSize(pix.size());//控制窗口图标大小
        if(this->max<this->min){
            this->max=8;
            this->isAnimation=false;
            timer2->stop();
        }
    });
}

//金币反转
void MyCoin::changeCoin(){
    if(this->flag){
        timer1->start(30);//每个30毫秒启动一次
        this->isAnimation=true;
        flag=false;
    }
    else{
        timer2->start(30);
        this->isAnimation=true;
        flag=true;
    }
}

//确保反金币动画在完成一次反转时间内不会被第二次点击中断并再次翻转
void MyCoin::mousePressEvent(QMouseEvent *e){
    if(this->isAnimation||this->isWin){
        return;
    }
    else{
        QPushButton::mousePressEvent(e);
    }
}
