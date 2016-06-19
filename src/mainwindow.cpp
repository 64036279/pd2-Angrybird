
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(960,540);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setBackgroundBrush(QPixmap(":/background/background.jpg").scaled(960,540));

        scoreboard = new QLabel(this);
        scoreboard->setStyleSheet("color:black; background-color: transparent; font: bold 25px;");
        scoreboard->setText("Score : 0");
        scoreboard->setGeometry(10, 0, 200, 60);
        scoreboard->show();
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));//BOX2D的重力加速度
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());//差30被
    // Create ground (You can edit here)
    itemList.push_back(new Land(16,2,32,4,QPixmap(":/ground.png").scaled(960,120),world,scene));

    slingshot *slingshot1 = new slingshot(100,360 , QPixmap(":/slingshot/slingshot.png").scaled(70,70),world,scene);
    // Create bird (You can edit here)
    birdie[0] = new Bird(5.0f,10.0f,1.0f,&timer,QPixmap(":/bird.png").scaled(60,60),world,scene);
     birdie[1] = new yellow(0.0f,10.0f,1.0f,&timer,QPixmap(":/yellow/yellow.png").scaled(60,60),world,scene);
     birdie[2] = new orange(0.0f,10.0f,1.0f,&timer,QPixmap(":/orange/orange.png").scaled(60,60),world,scene);
     birdie[3] = new blue(0.0f,10.0f,1.0f,&timer,QPixmap(":/blue/blue.png").scaled(60,60),world,scene);
    rival1[0] = new rival(22,5,1.5*0.5,&timer,QPixmap(":/rival/rival.png").scaled(1.5*30,1.5*30),world,scene);
        itemList.push_back(rival1[0]);

   /*rival1[1] = new rival(22,20,1.5*0.5,&timer,QPixmap(":/rival/rival.png").scaled(1.5*30,1.5*30),world,scene);
        itemList.push_back(rival1[1]);*/


    build[0] = new wood(22,15,5,1,&timer,QPixmap(":/wood1/wood1.png").scaled(150,30),world,scene);
      // wood1->wood(22,15,5,1,&timer,QPixmap(":/wood1/wood1.png").scaled(150,30),world,scene);
        itemList.push_back( build[0]);
    build[1] = new wood(20,10,1,5,&timer,QPixmap(":/wood2/wood2.png").scaled(30,150),world,scene);
      // wood2->wood(20,10,1,5,&timer,QPixmap(":/wood2/wood2.png").scaled(30,150),world,scene);
        itemList.push_back(build[1]);

    build[2] = new wood(24,10,1,5,&timer,QPixmap(":/wood2/wood2.png").scaled(30,150),world,scene);
       // wood3->wood(24,10,1,5,&timer,QPixmap(":/wood2/wood2.png").scaled(30,150),world,scene);
        itemList.push_back(build[2]);
    // Setting the Velocity
        birdie[0]->set_linear_velocity(b2Vec2(0,0));
   /* birdie->setLinearVelocity(b2Vec2(5,5));
    yellow1->setLinearVelocity(b2Vec2(0.01,20));
    orange1->setLinearVelocity(b2Vec2(10,1));
   blue1->setLinearVelocity(b2Vec2(10,1));*/
    itemList.push_back(birdie[0]);
    itemList.push_back(birdie[1]);
    itemList.push_back(birdie[2]);
    itemList.push_back(birdie[3]);

dead1 = false;

    // Timer

    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);

}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress)
     {
        beginx = QCursor::pos().x();
                beginy = QCursor::pos().y();

                //std::cout<<"the y is "<<beginy<<"\t";
               // std::cout<<"the x is "<<beginx<<"\t";


                if(beginx<=379 && beginx >=328 &&beginy>=457 &&beginy<=511)
                {
                    std::cout<<"i am inside \n";
                    right = 1;
                }
    }
    if(event->type() == QEvent::MouseMove)
    {

    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        endx = QCursor::pos().x();
               endy = QCursor::pos().y();
               diffx = (beginx - endx)*0.1;
               diffy = (endy - beginy)*0.1;
               if(right == 1  && which==1)
               {
                   birdie[0]->set_linear_velocity(b2Vec2(5,10));
                   right = 0;
                   birdie[1]->~QObject();//---------消掉鳥
                   birdie[1] = new Bird(5.0f,10.0f,1.0f,&timer,QPixmap(":/yellow/yellow.png").scaled(60,60),world,scene);
                   which+=1;
               }
               else if(right == 1  && which==2)
               {
                   birdie[1]->set_linear_velocity(b2Vec2(10,10));
                   right = 0;
                   birdie[2]->~QObject();//---------消掉鳥
                   birdie[2] = new Bird(5.0f,10.0f,1.0f,&timer,QPixmap(":/orange/orange.png").scaled(60,60),world,scene);
                   which+=1;
               }

              else if(right == 1  && which==3)
               {
                   birdie[2]->set_linear_velocity(b2Vec2(20,10));
                   right = 0;
                   birdie[3]->~QObject();//---------消掉鳥
                   birdie[3] = new Bird(5.0f,10.0f,1.0f,&timer,QPixmap(":/blue/blue.png").scaled(60,60),world,scene);
                   which+=1;
               }
               else if(right == 1  && which==4)
               {
                   birdie[3]->set_linear_velocity(b2Vec2(30,5));
                   right = 0;

                   which+=1;
               }
               //std::cout<<"the release x is"<<mouse_event->x()<<"\n";

               //TODO : add your code here
               //std::cout << "Release !" << std::endl ;
               //birdie[0]->set_linear_velocity(b2Vec2(5,3));



    }
    return false;
}


void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();

           if (dead1 == false){
                rival_1 = rival1[0]->get_linear_velocity().x + rival1[0]->get_linear_velocity().y;
                if (rival_1 > 2)
                {
                    dead1 = true;
                   rival1[0]->~QObject();
                    score += 1;


                }
           }


        //update scoreboard
        scoreboard->setText("Score :  " + QString::number(score));
    }


void MainWindow::QUITSLOT()
{
    // For debug
    this->close();
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow ::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R)
            {
        //std::cout << "LOL" << std::endl;
                birdie[0]->~QObject();
                birdie[1]->~QObject();
                birdie[2]->~QObject();
                 birdie[3]->~QObject();
                 if(dead1==false)
                 {
                     rival1[0]->~QObject();
                     //delete rival1[0];
                 }

                  build[0]->~QObject();
                  build[1]->~QObject();
                  build[2]->~QObject();
                 birdie[0] = new Bird(5.0f,10.0f,1.0f,&timer,QPixmap(":/bird.png").scaled(60,60),world,scene);
                  birdie[1] = new yellow(0.0f,10.0f,1.0f,&timer,QPixmap(":/yellow/yellow.png").scaled(60,60),world,scene);
                  birdie[2] = new orange(0.0f,10.0f,1.0f,&timer,QPixmap(":/orange/orange.png").scaled(60,60),world,scene);
                  birdie[3] = new blue(0.0f,10.0f,1.0f,&timer,QPixmap(":/blue/blue.png").scaled(60,60),world,scene);
                rival1[0] = new rival(22,5,1.5*0.5,&timer,QPixmap(":/rival/rival.png").scaled(1.5*30,1.5*30),world,scene);


                    build[0]=new wood(22,15,5,1,&timer,QPixmap(":/wood1/wood1.png").scaled(150,30),world,scene);


                    build[1]=new wood(20,10,1,5,&timer,QPixmap(":/wood2/wood2.png").scaled(30,150),world,scene);



                    build[2]=new wood(24,10,1,5,&timer,QPixmap(":/wood2/wood2.png").scaled(30,150),world,scene);

                which=1;
                score=0;
                dead1 = false;



            }
    if(event->key() == Qt::Key_L)
    {
        quitGame();
    }
}

