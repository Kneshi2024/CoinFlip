#ifndef CHOOSELEVELSENCE_H
#define CHOOSELEVELSENCE_H

#include <QMainWindow>
#include<playscene.h>

class ChooseLevelSence : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelSence(QWidget *parent = nullptr);

    //重写绘图事件paintEvent
    void paintEvent(QPaintEvent *event);
    //游戏场景指针
     PlayScene*play=NULL;

signals:
    void ChooseSenceBack();

};

#endif // CHOOSELEVELSENCE_H
