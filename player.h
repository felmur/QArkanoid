/*
 * QArkanoid
 * Simple "Arkanoid" type game, based on QT libraries
 * (c) 2020 by Felice Murolo, all rights reserved
 * licensed under GPL3, see LICENSE file
 * email: linuxboy@giove.tk
 * Location: Salerno, Italia
 *
*/
#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMediaPlaylist>
#include <QMediaPlayer>


class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(QGraphicsItem *parent=nullptr);
    int w=0;
    int h=0;
    void fire();
    void moveleft();
    void moveright();
    void moveto(QPoint p);

private:
    int speed=10;
    QMediaPlayer *firesnd=nullptr;

};

#endif // PLAYER_H
