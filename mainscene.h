#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include"chooselevelsence.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
//    show();
    ~MainScene();
    //重写paintEvent函数
    void paintEvent(QPaintEvent *event);
    //创建一个切换场景的指针让他指向空
    ChooseLevelSence*chooseSence=NULL;

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
