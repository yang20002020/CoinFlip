#include "playscene.h"
#include"mypushbutton.h"
#include<QPainter>
#include<QMenuBar>
#include<QLabel>
#include"coinbutton.h"
#include"dataconfig.h"
#include<QTimer>
#include<QMessageBox>
#include<QLabel> //胜利动画
#include<QPropertyAnimation>//胜利动画
#include<QSound>



PlayScene::PlayScene(int level,QWidget *parent) : MyMainWindow(parent)
{
    //胜利状态
    mHasWin=false;
    //返回按钮
    //将原来的函数QPushButton *btnBack=new QPushButton("Back",this);改为：
     MyPushButton *btnBack=new MyPushButton(":/res/BackButton.png",
                                          ":/res/BackButtonSelected.png",this);

     btnBack->resize(72,32);

    connect(btnBack,&QPushButton::clicked,this,&PlayScene::backBtnClicked);


    btnBack->move(this->width()-btnBack->width(),this->height()-btnBack->height());

    //添加左下角的label
    QLabel* label=new QLabel(this);
    label->setText(QString("Leve:%1").arg(level));//level 是第几关
    label->resize(150,50);

    //设置字体
    label->setFont(QFont("华文新魏",20));

    //移动到左下角
    label->move(30,this->height()-label->height());

    //取出第几关的二维数组数据
    dataConfig data;

    QVector<QVector<int>>dataArray=data.mData[level];//level是第几关



    //16个硬币按钮
    const int xoffset=57;
    const int yoffset=200;
    const int colWidth=50;
    const int rowHeight=50;

    for(int row=0;row<4;row++ )
    {
        for(int col=0;col<4;col++)
        {
            CoinButton *btn=new CoinButton(this);
            //存储按钮到第几行第几列
            mConts[row][col]=btn;//
            //x 坐标=列数*列宽
            //y 坐标=行数*行高
            int x=col*colWidth+xoffset;
            int y=row*rowHeight+yoffset;
           btn->setGeometry(x,y,50,50);
          // btn->setStat(1);改为
           //设置row行col列的数值
           btn->setStat(dataArray[row][col]);

           connect(btn,&CoinButton::clicked,[=]()
           {
               //每次点击硬币的时候改变状态，状态置反
               //btn->flip();//void CoinButton::flip()
               //修改如下
               this->flip(row,col); // void PlayScence::flip(int row, int col);

           });
        }
    }


}

void PlayScene::flip(int row, int col)
{
    //如果胜利了直接返回
    if(mHasWin)
    {
        return;
    }
    this->mConts[row][col]->flip();

    QSound::play(":/res/ConFlipSound.wav");

    //延迟翻转其他硬币
    QTimer ::singleShot(250,[=]()
    {
        //翻转上下左右的硬币
        if(row-1>=0)
        {
           this->mConts[row-1][col]->flip();//上
        }
        if(row+1<4)
        {
          this->mConts[row+1][col]->flip();//下
        }
        if(col-1>=0)
        {
          this->mConts[row][col-1]->flip();//左
        }
        if(col+1<4)
        {

            this->mConts[row][col+1]->flip();//右

        }
        //判断游戏是否胜利
        this->judgeWin();



    });


}

void PlayScene::judgeWin()
{
    //16个硬币按钮判断状态都是1

    for(int row=0;row<4;row++ )
    {
        for(int col=0;col<4;col++)
        {
            //银币继续
          if(!this->mConts[row][col]->stat())
              return;
        }
    }

    //所有都是金币的情况下游戏结束
   // QMessageBox::information(this,"恭喜","你已经胜利了");
    //胜利状态
     mHasWin=true;
  QSound::play(":/res/LevelWinSound.wav");
    //播放胜利动画
    QLabel*labelWin=new QLabel(this);
    QPixmap pix=QPixmap(":/res/LevelCompletedDialogBg.png");
    labelWin->setPixmap(pix);
    labelWin->resize(pix.size());
    labelWin->show();
  labelWin->move((this->width()-labelWin->width())/2,0);
    //labelWin->move((this->width()-labelWin->width())/2,-labelWin->width());//???

    QPropertyAnimation* animation=new QPropertyAnimation(labelWin,"geometry",this);
    animation->setStartValue(labelWin->geometry());
    animation->setEndValue(QRect(labelWin->x(),labelWin->y()+100,labelWin->width(),labelWin->height()));

    animation->setDuration(1000);
    //设置动画的运动曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //动画播放完自动删除动画对象
    animation->start(QAbstractAnimation::DeleteWhenStopped);


}

void PlayScene::paintEvent(QPaintEvent *event)
{

    //画背景

    QPainter painter(this);
    //搬动画家到菜单栏下面
    painter.translate(0,this->menuBar()->height());

    //绘制背景图片
    QPixmap  pix(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //绘制title 图片
    pix.load(":/res/Title.png");
    //将logo缩放
    pix=pix.scaled(pix.width()/2,pix.height()/2);

    painter.drawPixmap(0,0,pix);

}
