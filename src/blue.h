#ifndef BLUE_H
#define BLUE_H
#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include "bird.h"

class blue : public Bird
{
public:
    blue(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
   // void use();
};

#endif // BLUE_H
