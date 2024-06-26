#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include<QMouseEvent>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyButton(QWidget *parent = nullptr);
    MyButton(QString normalImage,QString pressImage="");//pressImage默认为空
    //设置成员变量
    QString normalImagePath;
    QString pressImagePath;
    void zoom1();//向下跳
    void zoom2();//向上跳
    //按下按钮
    void mousePressEvent(QMouseEvent *e);
    //松开按钮
    void mouseReleaseEvent(QMouseEvent *e);


signals:

};

#endif // MYBUTTON_H
