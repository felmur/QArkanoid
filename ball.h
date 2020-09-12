/*
 * QArkanoid
 * Simple "Arkanoid" type game, based on QT libraries
 * (c) 2020 by Felice Murolo, all rights reserved
 * licensed under GPL3, see LICENSE file
 * email: linuxboy@giove.tk
 * Location: Salerno, Italia
 *
*/
#ifndef BALL_H
#define BALL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QMediaPlaylist>
#include <QMediaPlayer>

class Ball : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Ball(QGraphicsItem *parent=nullptr);
    int w=0;
    int h=0;
    bool launched=false;
    void setLaunched(bool value);

private slots:
    void move();

private:
    int speedx=-3;
    int speedy=-3;
    QMediaPlayer *popbrick = nullptr;
    QMediaPlayer *popplayer = nullptr;
    QMediaPlayer *popborder = nullptr;
    void playBorderSnd();
    bool antibump=false;

signals:
    void ballLose();
    void brickFinished();
    void brickHit(int bricktype);
};

#endif // BALL_H
