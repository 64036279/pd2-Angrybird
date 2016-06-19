#ifndef ORANGE_H
#define ORANGE_H
#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include "bird.h"

class orange: public Bird
{
public:
    orange(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    //void use();

};

#endif // ORANGE_H
