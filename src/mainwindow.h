#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QLabel>
#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <yellow.h>
#include <blue.h>
#include <orange.h>
#include <wood.h>
#include <rival.h>
#include <slingshot.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
     bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent *event);


    //{
signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    Land *land;
    slingshot *slingshot1;
    QLabel *scoreboard;
    int beginy,beginx,right,endx,endy,diffx,diffy,which=1;
    float rival_1;
    int score=0;
    wood *build[3];
    rival *rival1[1];
    Bird *birdie[4];
   bool dead1=false;

};

#endif // MAINWINDOW_H
