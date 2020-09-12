/*
 * QArkanoid
 * Simple "Arkanoid" type game, based on QT libraries
 * (c) 2020 by Felice Murolo, all rights reserved
 * licensed under GPL3, see LICENSE file
 * email: linuxboy@giove.tk
 * Location: Salerno, Italia
 *
*/

#include "ball.h"
#include "global.h"
#include "player.h"
#include "brick.h"

Ball::Ball(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/blueball"));
    w = pixmap().width();
    h = pixmap().height();
    launched = false;
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(move()));
    timer->start(10);

    // prepare brick destroyed sound
    QMediaPlaylist *plbrick = new QMediaPlaylist();
    plbrick->addMedia(QUrl("qrc:/sounds/popbrick"));
    popbrick = new QMediaPlayer();
    popbrick->setPlaylist(plbrick);

    // prepare player collide sound
    QMediaPlaylist *plplayer = new QMediaPlaylist();
    plplayer->addMedia(QUrl("qrc:/sounds/pop"));
    popplayer = new QMediaPlayer();
    popplayer->setPlaylist(plplayer);

    // prepare boing sound
    QMediaPlaylist *plboing = new QMediaPlaylist();
    plboing->addMedia(QUrl("qrc:/sounds/boing"));
    popborder = new QMediaPlayer();
    popborder->setPlaylist(plboing);

}

void Ball::setLaunched(bool value)
{
    launched = value;
}

void Ball::move()
{
    // ball is lost
    if (y()> gheight-50) {
        // PLAYER LOSE
        qDebug() << "Ball is lost";
        launched = false;
        emit(ballLose());
    }

    if (launched) {
        QList<QGraphicsItem *> colliding_items = collidingItems();
        // collision with player or bricks
         for(auto i : colliding_items) {
             if (typeid(*i) == typeid (Player) && !antibump) {
                 popplayer->play();
                 speedy = -speedy;
                 setPos(x()+speedx, y()+speedy);
                 antibump = true;   // disable bumps until the ball touches another element.
                 return;
             }
             else if (typeid(*i) == typeid (Brick)) {
                 antibump=false;
                 Brick *b = (Brick *)i;
                 int tp = b->tp;
                 if (popbrick->state() == QMediaPlayer::PlayingState) popbrick->setPosition(7);
                 else if (popbrick->state() == QMediaPlayer::StoppedState) popbrick->play();
                 emit(brickHit(tp));
                 speedy = -speedy;
                 setPos(x()+speedx, y()+speedy);
                 scene()->removeItem(i);
                 delete(i);
                 // check if bricks are finished
                 bool brickfinished=true;
                 for (auto j : scene()->items()) {
                     if (typeid(*j) == typeid(Brick)) {
                         brickfinished = false;
                         break;
                     }
                 }
                 if (brickfinished) {
                     qDebug() << "Bricks Finished";
                     launched = false;
                     emit(brickFinished());
                 }
                 return;
             }
        }
        // collision with borders
        int sx = x()+speedx;
        int sy = y()+speedy;
        if (sx<0 || sx+w>gwidth) {
            speedx = -speedx;
            playBorderSnd();
            antibump=false;
        }
        if (sy<0 || sy+h>gheight) {
            speedy = -speedy;
            playBorderSnd();
            antibump=false;
        }
        setPos(x()+speedx, y()+speedy);
    }
}

void Ball::playBorderSnd(){
    if (popborder->state() == QMediaPlayer::PlayingState) popborder->setPosition(0);
    else if (popborder->state() == QMediaPlayer::StoppedState) popborder->play();
}
