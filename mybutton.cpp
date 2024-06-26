#include "mybutton.h"
#include<QDebug>
#include<QPropertyAnimation>
#include<QMouseEvent>

//MyButton::MyButton(QWidget *parent) : QWidget(parent)
//{

//}
MyButton::MyButton(QString normalImage,QString pressImage){
    this->normalImagePath=normalImage;
    this->pressImagePath=pressImage;
    QPixmap pix;
    bool ret = pix.load(normalImage);
    if(!ret){
        qDebug()<<"图片加载失败";
        return ;
    }

    //设置图片大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px}");
    //设置图标
    this->setIcon(QIcon(pix));
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

}

//向下跳
void MyButton::zoom1(){
    //创建动态对象
    QPropertyAnimation*Animation=new QPropertyAnimation(this,"geometry");//几何矩形
    //设置动态时间
    Animation->setCurrentTime(200);
    //设置初始位置
    Animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置结束位置
    Animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置弹跳曲线
    Animation->setEasingCurve(QEasingCurve::OutBounce);
    //启用
    Animation->start();



}

//向上跳
void MyButton::zoom2(){
    //创建动态对象
    QPropertyAnimation*Animation=new QPropertyAnimation(this,"geometry");//几何矩形
    //设置动态时间
    Animation->setCurrentTime(200);
    //设置初始位置
    Animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置结束位置
    Animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置弹跳曲线
    Animation->setEasingCurve(QEasingCurve::OutBounce);
    //启用
    Animation->start();

}

//按下按钮
void MyButton::mousePressEvent(QMouseEvent *e){
    if(this->pressImagePath!=""){
        QPixmap pix;
        bool ret = pix.load(this->pressImagePath);
        if(!ret){
            qDebug()<<"图片加载失败";
            return ;
        }

        //设置图片大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px}");
        //设置图标
        this->setIcon(QIcon(pix));
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mousePressEvent(e);

}
//松开按钮
void MyButton::mouseReleaseEvent(QMouseEvent *e){
    if(this->pressImagePath!=""){
        QPixmap pix;
        bool ret=pix.load(this->normalImagePath);
        if(!ret){
            qDebug()<<"图片加载失败";
            return ;
        }

        //设置图片大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px}");
        //设置图标
        this->setIcon(QIcon(pix));
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}

