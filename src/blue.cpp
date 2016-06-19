#include "blue.h"

blue::blue(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x, y,  radius,  timer, pixmap,  world,  scene)
{

}


/*void blue::use()
{
    if(effect)
        {
            effect=false;
            g_body->SetLinearVelocity(b2Vec2(-15,-1));
        }
}*/


