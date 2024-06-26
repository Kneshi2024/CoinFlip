#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include"mybutton.h"
#include<QDebug>
#include<QTimer>
#include<QMediaPlayer>
#include<QUrl>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //设置固定大小
    setFixedSize(320,588);
    //设置非固定大小
    // resize(320,588);
    // setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //设置窗口图标
    setWindowIcon(QIcon(":/Image/Coin0001.png"));
    //设置窗口名称
    setWindowTitle("老姬带你翻金币");
    //实现退出按钮
    connect(ui->actionquit,&QAction::triggered,[=](){
       this->close();
    });
    //开始按钮
    MyButton*StartButton=new MyButton(":/Image/MenuSceneStartButton.png");
    StartButton->setParent(this);//将其放入窗口中
    StartButton->move(this->width()*0.5-StartButton->width()*0.5,this->height()*0.7);

    //设置开始按钮音效
    QMediaPlayer*startSound=new QMediaPlayer(this);
    QString audioFilePath6="/Image/TapButtonSound.wav";
    QUrl audioFile6=QUrl::fromLocalFile(audioFilePath6);
    startSound->setSource(audioFile6);

    //实例化切换场景对象
     chooseSence=new ChooseLevelSence;
     //监听选择关卡返回按钮信号
     connect(chooseSence,&ChooseLevelSence::ChooseSenceBack,[=](){
         this->setGeometry(chooseSence->geometry());
         chooseSence->hide();
         this->show();

     });

     //点击开始按钮实现
    connect(StartButton,&MyButton::clicked,[=](){
        //qDebug()<<"点击了开始按钮";
        //startSound->setLoops(-1);无限循环音效
        startSound->play();
        //设置点击特效
        StartButton->zoom1();
        StartButton->zoom2();
        //延时切换场景
        QTimer::singleShot(400,this,[=](){
            chooseSence->setGeometry(this->geometry());
            this->hide();
            chooseSence->show();
        });
    });
}

MainScene::~MainScene()
{
    delete ui;
}

//重写paintEvent函数
void MainScene::paintEvent(QPaintEvent *event){
    (void)event;
    QPainter paint(this);
    QPixmap pix;
    //背景图片
    pix.load(":/Image/PlayLevelSceneBg.png");
    paint.drawPixmap(0,0,this->width(),this->height(),pix);
    //背景图标
    pix.load(":/Image/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    paint.drawPixmap(10,30,pix);


}

