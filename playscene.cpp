#include "playscene.h"
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include"mybutton.h"
#include<QTimer>
#include<QLabel>
#include<QFont>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QMediaPlayer>
#include<QUrl>

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}
PlayScene::PlayScene(int levelnum){
    qDebug()<<QString("进入了第%1关").arg(levelnum);
    this->LevelNum=levelnum;
    //初始化窗口
    //设置固定大小
    this->setFixedSize(320,588);
    //设置窗口图标
    this->setWindowIcon(QIcon(":/Image/Coin0001.png"));
    //设置标题
    this->setWindowTitle("老姬带你虾扯蛋");
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
    //将按钮放入窗口中
    backBtn->setParent(this);
    //设置按钮位置
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    //设置返回按钮音效
    QMediaPlayer*backSound=new QMediaPlayer(this);
    QString audioFilePath3="/Image/BackButtonSound.wav";
    QUrl audioFile3=QUrl::fromLocalFile(audioFilePath3);
    backSound->setSource(audioFile3);
    //点击返回响应
    connect(backBtn,MyButton::clicked,[=](){
        //qDebug()<<"返金币场景中:点击了返回按钮";
        backSound->play();
        //发送按了返回的信号
        QTimer::singleShot(300,this,[=](){
            emit ChooseSceneBack2();
        });
    });
    //显示当前关卡
    QLabel*label=new QLabel;
    QString str1=QString("Level:%1").arg(levelnum);
    label->setText(str1);
    label->setParent(this);
    label->setGeometry(30,this->height()-50,120,50);//设置label的大小和位置
    //设置字体、大小
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);

    //初始化每个关卡的二维数组
    dataConfig config;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            gameArray[i][j]=config.mData[this->LevelNum][i][j];//用二维数组记录关卡数据
        }
    }

    //胜利图片载入
    QLabel*WinLabel=new QLabel;
    QPixmap pix;
    pix.load(":/Image/LevelCompletedDialogBg.png");
    WinLabel->setGeometry(0,0,pix.width(),pix.height());
    WinLabel->setPixmap(pix);
    WinLabel->setParent(this);
    WinLabel->move(this->width()*0.5-pix.width()*0.5,-pix.height());

    //设置翻金币按钮音效
    QMediaPlayer*changeSound=new QMediaPlayer(this);
    QString audioFilePath4="/Image/ConFlipSound.wav";
    QUrl audioFile4=QUrl::fromLocalFile(audioFilePath4);
    changeSound->setSource(audioFile4);
    //设置胜利音效
    QMediaPlayer*winSound=new QMediaPlayer(this);
    QString audioFilePath5="/Image/LevelWinSound.wav";
    QUrl audioFile5=QUrl::fromLocalFile(audioFilePath5);
    winSound->setSource(audioFile5);

    //显示金币背景图案
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            QLabel*label1=new QLabel;
            label1->setParent(this);
            label1->setGeometry(0,0,50,50);//每次循环重新创建图形再原点
            label1->setPixmap(QPixmap(":/Image/BoardNode.png"));
            label1->move(57+i*50,200+j*50);//每次循环从新创建在原点的图形移动一次

            QString str;
            if(gameArray[i][j]==1){
                str=":/Image/Coin0001.png";
            }
            else{
                str=":/Image/Coin0008.png";
            }
            //创建金币
            MyCoin*coin=new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            coin->Xpos=i;
            coin->Ypos=j;
            coin->flag=gameArray[i][j];//1为正面  0为反面
            //将coin全部记录在二维数组中，以便之后通过二维数组寻找coin的上下左右相邻按钮
            coinBtn[i][j]=coin;

            //点击金币反转
            connect(coin,&MyCoin::clicked,[=](){
                coin->changeCoin();
                changeSound->play();
                this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;
                //点击按钮禁用全部按钮
                for(int i=0;i<4;i++){
                    for(int j=0;j<4;j++){
                        this->coinBtn[i][j]->isWin=true;
                    }
                }
                //qDebug()<<gameArray[i][j];
                //反转相邻的金币
                QTimer::singleShot(300,this,[=](){
                    //右边
                    if(coin->Xpos+1<=3){
                        coinBtn[coin->Xpos+1][coin->Ypos]->changeCoin();
                        this->gameArray[coin->Xpos+1][coin->Ypos]=this->gameArray[coin->Xpos+1][coin->Ypos]==0?1:0;
                    }
                    //左边
                    if(coin->Xpos-1>=0){
                        coinBtn[coin->Xpos-1][coin->Ypos]->changeCoin();
                        this->gameArray[coin->Xpos-1][coin->Ypos]=this->gameArray[coin->Xpos-1][coin->Ypos]==0?1:0;
                    }
                    //下面
                    if(coin->Ypos+1<=3){
                        coinBtn[coin->Xpos][coin->Ypos+1]->changeCoin();
                        this->gameArray[coin->Xpos][coin->Ypos+1]=this->gameArray[coin->Xpos][coin->Ypos+1]==0?1:0;
                    }
                    //上面
                    if(coin->Ypos-1>=0){
                        coinBtn[coin->Xpos][coin->Ypos-1]->changeCoin();
                        this->gameArray[coin->Xpos][coin->Ypos-1]=this->gameArray[coin->Xpos][coin->Ypos-1]==0?1:0;
                    }
                    //解除所有按钮的限制
                    for(int i=0;i<4;i++){
                        for(int j=0;j<4;j++){
                            this->coinBtn[i][j]->isWin=false;
                        }
                    }
                    //判断是否胜利
                    this->isWin=true;
                    for(int i=0;i<4;i++){
                        for(int j=0;j<4;j++){
                            if(this->coinBtn[i][j]->flag==false){
                                this->isWin=false;
                                break;
                            }
                        }
                    }
                    if(this->isWin==true){
                        //qDebug()<<"游戏胜利!";
                        winSound->play();
                        for(int i=0;i<4;i++){
                            for(int j=0;j<4;j++){
                                coinBtn[i][j]->isWin=true;
                            }
                        }
                        QPropertyAnimation*animation=new QPropertyAnimation(WinLabel,"geometry");
                        //设置时间间隔
                        animation->setCurrentTime(1000);
                        //设置起始位置
                        animation->setStartValue(QRect(WinLabel->x(),WinLabel->y(),WinLabel->width(),WinLabel->height()));
                        //设置终点位置
                        animation->setEndValue(QRect(WinLabel->x(),WinLabel->y()+180,WinLabel->width(),WinLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }
                });
            });
        }
    }
}

//重构paintEvent函数（利用画家画出窗口背景）
void PlayScene::paintEvent(QPaintEvent *event){
    (void)event;
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Image/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/Image/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}
