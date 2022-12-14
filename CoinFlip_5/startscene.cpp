#include "startscene.h"
#include<QPushButton>
#include"mypushbutton.h"
#include<QTimer>
#include<QSound> //项目文件需要加模块
//QT += core gui multimedia

StartScene::StartScene(QWidget* parent) :  MyMainWindow(parent)
{
  this->setWindowTitle("开始场景");

   MyPushButton*btnStart=new MyPushButton(":/res/MenuSceneStartButton.png",
                                          ":/res/MenuSceneStartButton.png",this);
   btnStart->resize(114,114);

   //按钮水平居中，垂直方向在3/4位置
   //计算方式 ，窗口宽度/2，按钮宽度/2，y=窗口宽度*3/4-按钮高度/2

   btnStart->move((this->width()-btnStart->width())/2,
                  this->height()*3/4-btnStart->height()/2);

   //当窗口SelectScene的返回按钮点击的时候,显示窗口StartScene，隐藏窗口SelectScene
   connect(&mSelectScence,&SelectScene::backBtnClicked,[=]()
   {
       QSound::play(":/res/BackButtonSound.wav");
       this->mSelectScence.hide();
       this->show();
       this->move( this->mSelectScence.pos());
   });

   //开始按钮被点击
   connect(btnStart,&MyPushButton::clicked,[=]()
   {
       QSound::play(":/res/TapButtonSound.wav");
       //将按钮设置为不可用
       btnStart->setEnabled(false);
       //播放向下的动画
       btnStart->moveDonw();
       QTimer::singleShot(150,[=]()
       {
           //往上的动画会覆盖之前的动画
          //要等待之前动画播放完毕再调用
          //播放向上的动画，
           btnStart->moveUp();

       });
       QTimer ::singleShot(300,[=]()
       {
           //将按钮设置为可用
           btnStart->setEnabled(true);

           //场景转化
           //隐藏当前窗口
           this->hide();
           //显示第二个窗口
           this->mSelectScence.show();
           //将窗口移动到当前位置
           this->mSelectScence.move(this->pos());




       });



   });
}
