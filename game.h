/*
 * QArkanoid
 * Simple "Arkanoid" type game, based on QT libraries
 * (c) 2020 by Felice Murolo, all rights reserved
 * licensed under GPL3, see LICENSE file
 * email: linuxboy@giove.tk
 * Location: Salerno, Italia
 *
*/
#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>
#include <QFontDatabase>
#include <QGraphicsTextItem>
#include <QFont>
#include "global.h"
#include "player.h"
#include "ball.h"
#include "brick.h"



class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QGraphicsView *parent=nullptr);
    Player *player=nullptr;
    Ball *ball=nullptr;

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    void addBricks();
    void showHud();
    void gameOver();
    QFont myfont24;
    QFont myfont36;
    QGraphicsScene *scene=nullptr;
    int lives = 3;  // player lives
    int points = 0; // player points
    QGraphicsTextItem *txtHud=nullptr;
    QMediaPlayer *loseball=nullptr;

private slots:
    void playerLose();
    void playerWin();
    void setPoints(int bricktype);
};

#endif // GAME_H
