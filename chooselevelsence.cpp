#include "chooselevelsence.h"
#include<QMenuBar>
#include<QPainter>
#include"mybutton.h"
#include<QDebug>
#include<QTimer>
#include<QLabel>
#include"playscene.h"
#include<QMediaPlayer>
#include<QUrl>

ChooseLevelSence::ChooseLevelSence(QWidget *parent) : QMainWindow(parent)
{
    //设置固定大小
    this->setFixedSize(320,588);
    //设置窗口图标
    this->setWindowIcon(QIcon(":/Image/Coin0001.png"));
    //设置标题
    this->setWindowTitle("老姬带你选关卡");
    //设置开始菜单
    QMenuBar*bar= menuBar();
    //放入窗口
    setMenuBar(bar);
    //创建开始菜单
    QMenu* startmenu=bar->addMenu("哈哈");//用startmenu接收addMenu方便下条创建
    //创建开始菜单下的退出选项
    QAction*quitSence= startmenu->addAction("退出");//用quitSence接收addAction方便下条调用
    //创建退出选项的真实用途
    connect(quitSence,&QAction::triggered,[=](){
        this->close();
    });
    //创建返回按钮
    MyButton*backBtn=new MyButton(":/Image/BackButton.png",":/Image/BackButtonSelected.png");
    //将返回按钮放入窗口中
    backBtn->setParent(this);
    //设置返回按钮位置
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    //设置返回按钮音效
    QMediaPlayer*backSound=new QMediaPlayer(this);
    QString audioFilePath="/Image/BackButtonSound.wav";
    QUrl audioFile=QUrl::fromLocalFile(audioFilePath);
    backSound->setSource(audioFile);
    //点击返回响应
    connect(backBtn,MyButton::clicked,[=](){
        //qDebug()<<"点击了返回按钮";
        backSound->play();
        //发送按了返回的信号
        QTimer::singleShot(300,this,[=](){
            emit ChooseSenceBack();
            this->hide();
        });
    });

    //设置选择按钮音效
    QMediaPlayer*chooseSound=new QMediaPlayer(this);
    QString audioFilePath2="/Image/TapButtonSound.wav";
    QUrl audioFile2=QUrl::fromLocalFile(audioFilePath2);
    chooseSound->setSource(audioFile2);

    //创建关卡选择按钮
    for(int i=0;i<20;i++){
        MyButton*menuBtn=new MyButton(":/Image/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+i%4*70,130+i/4*70);
        //点击触发关卡
        connect(menuBtn,&MyButton::clicked,[=](){
            //QString str=QString("您选择了第%1关卡").arg(QString::number(i+1));
            //qDebug()<<str;
            chooseSound->play();
            play=new PlayScene(i+1);
            play->setGeometry(this->geometry());
            this->hide();
            play->show();
            connect(play,&PlayScene::ChooseSceneBack2,[=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play=NULL;
            });

        });
        //用label设置数字
        QLabel*label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);
        //设置label对齐方式(居中)
        label->setAlignment(Qt::AlignCenter);
        //让鼠标穿透label点击到menuBtn  51号
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}



//重写绘图事件paintEvent
void ChooseLevelSence::paintEvent(QPaintEvent *event){
    (void)event;
    QPainter paint(this);
    QPixmap pix;
    //选择背景图片
    pix.load(":/Image/OtherSceneBg.png");
    //画入背景图片
    paint.drawPixmap(0,0,this->width(),this->height(),pix);
    //选择插入图标
    pix.load(":/Image/Title.png");
    //插入图标
    paint.drawPixmap((this->width()-pix.width())*0.5,30,pix);
}
