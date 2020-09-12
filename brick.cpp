/*
 * QArkanoid
 * Simple "Arkanoid" type game, based on QT libraries
 * (c) 2020 by Felice Murolo, all rights reserved
 * licensed under GPL3, see LICENSE file
 * email: linuxboy@giove.tk
 * Location: Salerno, Italia
 *
*/

#include "brick.h"

Brick::Brick(QPixmap *pmap, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(*pmap);
    w = pixmap().width();
    h = pixmap().height();
}

