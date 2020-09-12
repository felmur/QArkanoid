/*
 * QArkanoid
 * Simple "Arkanoid" type game, based on QT libraries
 * (c) 2020 by Felice Murolo, all rights reserved
 * licensed under GPL3, see LICENSE file
 * email: linuxboy@giove.tk
 * Location: Salerno, Italia
 *
*/

#include "player.h"
#include "global.h"
#include <QDebug>


Player::Player(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/player"));
    w = pixmap().width();
    h = pixmap().height();

    // prepare fire sound
    QMediaPlaylist *plfire = new QMediaPlaylist();
    plfire->addMedia(QUrl("qrc:/sounds/fire"));
    firesnd = new QMediaPlayer();
    firesnd->setPlaylist(plfire);

}

void Player::fire(){
    qDebug() << "FIRE";
    firesnd->play();
}

void Player::moveleft()
{
    int px = x();
    px = px - speed;
    moveto(QPoint(px,y()));
}

void Player::moveright()
{
    int px = x();
    px = px + speed;
    moveto(QPoint(px,y()));

}

void Player::moveto(QPoint p)
{
    int x = p.x();
    if (x < 0) x = 0;
    if (x > gwidth-w) x = gwidth - w;
    setPos(x,y());
}
