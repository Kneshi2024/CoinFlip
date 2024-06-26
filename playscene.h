#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelnum);
    int LevelNum;
    //重构paintEvent函数（利用画家画出窗口背景）
    void paintEvent(QPaintEvent *event);
    int gameArray[4][4];//二维数组维护每个关卡的具体数据
    //创建二维数组记录coin的值
    MyCoin*coinBtn[4][4];
    //判断是否胜利
    bool isWin;


signals:
    void ChooseSceneBack2();

};

#endif // PLAYSCENE_H
