#include "selectscene.h"
#include<QPushButton>
#include<QMenuBar>
#include"mypushbutton.h"
#include"playscene.h"
#include<QSound>


SelectScene::SelectScene(QWidget* parent) : MyMainWindow(parent)
{
   //将原来的函数QPushButton *btnBack=new QPushButton("Back",this);改为：
    MyPushButton *btnBack=new MyPushButton(":/res/BackButton.png",
                                         ":/res/BackButtonSelected.png",this);

    btnBack->resize(72,32);

   connect(btnBack,&QPushButton::clicked,this,&SelectScene::backBtnClicked);


   btnBack->move(this->width()-btnBack->width(),this->height()-btnBack->height());

   //关卡按钮20个
   const int colWidth=70;
   const int rowHeight=70;

   //x y 偏移
   const  int xoffset=25;
   const  int yoffset=130;

   for(int i=0;i<20;i++)
   {
       MyPushButton* btn=new MyPushButton(":/res/LevelIcon.png",":/res/LevelIcon.png",this);
       btn->setText(QString::number(i+1));
       //排列
       //行 i/4
       //列 i%4
       int col=i%4;//x (0\1\2\3)
       int row=i/4;//y (0\1\2\3\4)

       //x 坐标=列数*列宽
       //y 坐标=行数*行高
       int x=col*colWidth+xoffset;
       int y=row*rowHeight+yoffset;
       btn->resize(57,57);
       btn->move(x,y);
      //点击关卡后打开一个新的场景playScene
       connect(btn,&MyPushButton::clicked,[=]()
       {
             QSound::play(":/res/TapButtonSound.wav");
           //PlayScene(int level,QWidget *parent = nullptr);
           PlayScene* playScene=new PlayScene(i+1);//第几关

           //设置playscene关闭的时候自动释放
           playScene->setAttribute(Qt::WA_DeleteOnClose);
           //Makes Qt delete this widget
           //when the widget has accepted the close event (see QWidget::closeEvent()).
           playScene->show();
           playScene->move(this->pos());
           this->hide();

           connect(playScene,&PlayScene::backBtnClicked,[=]()
           {
               QSound::play(":/res/BackButtonSelected.png");

               this->move(playScene->pos());
               this->show();
               //使用关闭
               playScene->close();

           });
       });
   }


}

void SelectScene::paintEvent(QPaintEvent* event)
{

    QPainter painter(this);
    //搬动画家到菜单栏下面
    painter.translate(0,this->menuBar()->height());

    //绘制背景图片
    QPixmap  pix(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //绘制title 图片
    pix.load(":/res/Title.png");
    painter.drawPixmap(0,0,pix);

}
