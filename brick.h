/*
 * QArkanoid
 * Simple "Arkanoid" type game, based on QT libraries
 * (c) 2020 by Felice Murolo, all rights reserved
 * licensed under GPL3, see LICENSE file
 * email: linuxboy@giove.tk
 * Location: Salerno, Italia
 *
*/
#ifndef BRICK_H
#define BRICK_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPixmap>

class Brick : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Brick(QPixmap *pmap, QGraphicsItem *parent=nullptr);
    int w=0;
    int h=0;
    enum tps { Yellow=1, Green, Blue, Red, Purple, Grey };
    int tp=0;
};

#endif // BRICK_H
