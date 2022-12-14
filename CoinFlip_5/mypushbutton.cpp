#include "mypushbutton.h"
#include<QPainter>
#include<QPropertyAnimation>

MyPushButton::MyPushButton(QString normalImg,QString pressedImg,  QWidget *parent)
    : QPushButton(parent),
      mNormalImg(normalImg),
      mPressedImg(pressedImg)

{
   mStat=Normal;



}

void MyPushButton::moveDonw()
{

    //1位置大小属性发生变化
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry",this);
    //第一个参数  是当前对象；第三个对象 是父对象；第二个对象？？？？？？
    //QPropertyAnimation(QObject *target, const QByteArray &propertyName, QObject *parent = Q_NULLPTR)

    //2给定开始的位置大小属性
    animation->setStartValue(this->geometry());

    //3给定结束的位置大小属性
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //4给定速度，给定动画时长
    animation->setDuration(100);


    animation->start(QAbstractAnimation::DeleteWhenStopped);
    //The animation will be automatically deleted when stopped.（delete new 对象）


}

void MyPushButton::moveUp()
{

    //1位置大小属性发生变化
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry",this);
    //第一个参数  是当前对象；第三个对象 是父对象；第二个对象？？？？？？
    //QPropertyAnimation(QObject *target, const QByteArray &propertyName, QObject *parent = Q_NULLPTR)

    //2给定开始的位置大小属性
    animation->setStartValue(this->geometry());

    //3给定结束的位置大小属性
    animation->setEndValue(QRect(this->x(),this->y()-10,this->width(),this->height()));

    //4给定速度，给定动画时长
    animation->setDuration(100);


    animation->start(QAbstractAnimation::DeleteWhenStopped);
    //The animation will be automatically deleted when stopped.（delete new 对象）


}

void MyPushButton::paintEvent(QPaintEvent* ev)
{
    //绘制按钮的图片
    QPainter painer(this);

    QPixmap  pix;
    if(mStat==Normal)
        pix.load(mNormalImg);
    if(mStat==pressed)
        pix.load(mPressedImg);
    painer.drawPixmap(0,0,this->width(),this->height(),pix);//坐标 0?  0?
    //void QPainter::drawPixmap(int x, int y, int width, int height, const QPixmap &pixmap)


    //绘制按钮的文字
    painer.drawText(0,0,this->width(),this->height(),
                    Qt::AlignHCenter|Qt::AlignVCenter,this->text());

}
void MyPushButton:: mousePressEvent(QMouseEvent* e)
{
    //鼠标按下的时候状态
    this->mStat=pressed;
    update();
    //保证信号和槽功能
    QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent* e)
{
    //鼠标松开的时候状态
    this->mStat=Normal;
    update();

    QPushButton::mouseReleaseEvent(e);
}
