#include "orange.h"

orange::orange(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) :Bird(x, y,  radius,  timer, pixmap,  world,  scene)
{

}

/*void orange::use()
{
    if(effect && BeenFire)
       {
           g_body->SetLinearVelocity(b2Vec2(0.01,-20));
           effect=false;
       }
}*/
