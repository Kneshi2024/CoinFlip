#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString coinpath);
    QString CoinPath;
    //金币X坐标
    int Xpos;
    //金币Y坐标
    int Ypos;
    //金币正反面标识
    bool flag;
    //反动金币函数
    void changeCoin();
    //正面反反面计时器
    QTimer *timer1;
    //反面反正面计时器
    QTimer *timer2;
    int min=1;
    int max=8;
    //正在执行动画标识
    bool isAnimation=false;
    //重写mousePressEvent保证动画播放完毕
    void mousePressEvent(QMouseEvent *e);
    //判断胜利标志（使胜利后不在可以点击coin按钮）
    bool isWin=false;

signals:

};

#endif // MYCOIN_H
