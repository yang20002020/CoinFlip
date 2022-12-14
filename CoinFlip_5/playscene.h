#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"mymainwindow.h"
#include"coinbutton.h"  //添加

class PlayScene : public MyMainWindow
{
    Q_OBJECT
public:
   PlayScene(int level,QWidget *parent = nullptr);
   //翻row行，col列的硬币
   void flip(int row, int col);

   //判断胜利
    void  judgeWin();

signals:
    void backBtnClicked();
protected:
    void paintEvent(QPaintEvent*event);

public slots:

private:
    CoinButton* mConts[4][4];  //添加  ？？？？
    //胜利的状态
    bool mHasWin;
};

#endif // PLAYSCENE_H
