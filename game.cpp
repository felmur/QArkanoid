/*
 * QArkanoid
 * Simple "Arkanoid" type game, based on QT libraries
 * (c) 2020 by Felice Murolo, all rights reserved
 * licensed under GPL3, see LICENSE file
 * email: linuxboy@giove.tk
 * Location: Salerno, Italia
 *
*/

#include "game.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QIcon>
#include <QMediaPlayer>
#include <QMediaPlaylist>


Game::Game(QGraphicsView *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,gwidth,gheight);
    scene->setBackgroundBrush(QBrush(QImage(":/images/back")));

    window()->setWindowTitle(prgname+" v"+version);
    window()->setWindowIcon(QIcon(":/images/icon"));
    setFixedSize(gwidth,gheight);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(scene);

    player = new Player();
    player->setPos((gwidth - player->w)/2,gheight-100);
    scene->addItem(player);

    ball = new Ball();
    ball->setPos(player->x() + (player->w - ball->w)/2, player->y() - ball->h);
    connect(ball, SIGNAL(ballLose()),this,SLOT(playerLose()));
    connect(ball, SIGNAL(brickFinished()),this,SLOT(playerWin()));
    connect(ball, SIGNAL(brickHit(int)),this,SLOT(setPoints(int)));
    scene->addItem(ball);

    int id = QFontDatabase::addApplicationFont(":/fonts/mainfont");
    if (id>=0) {
        qDebug() << "Fonts loaded";
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        myfont24 = QFont(family,24);
        myfont36 = QFont(family,36);
    }
    else {
        qDebug() << "ERROR LOADING FONTS, FALLBACK TO 'TIMES'";
    }

    txtHud = new QGraphicsTextItem();
    txtHud->setDefaultTextColor(Qt::green);
    txtHud->setFont(myfont24);
    showHud();

    addBricks();

    setCursor(Qt::BlankCursor);
    setMouseTracking(true);

    // add background sound loop
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/loop"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->setVolume(10);
    music->play();

    // prepare loseball sound
    QMediaPlaylist *plball = new QMediaPlaylist();
    plball->addMedia(QUrl("qrc:/sounds/loseball"));
    loseball = new QMediaPlayer();
    loseball->setPlaylist(plball);

    show();
}


void Game::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){

    case Qt::Key_Left:
        if (player) {
            player->moveleft();
            if (!ball->launched) ball->setPos(player->x() + (player->w - ball->w)/2, player->y() - ball->h);
        }
        break;

    case Qt::Key_Right:
        if (player) {
            player->moveright();
            if (!ball->launched) ball->setPos(player->x() + (player->w - ball->w)/2, player->y() - ball->h);
        }
        break;

    case Qt::Key_Space:
        if (player) {
            player->fire();
            ball->setLaunched(true);
        }
        break;
    }
}

void Game::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {

    case Qt::LeftButton:
        if (player) {
            player->fire();
            ball->setLaunched(true);
        }
        break;

    case Qt::RightButton:
        qDebug() << "MOUSE RIGHT PRESS";
        break;

    default:
        qDebug() << "OTHER MOUSE";
        break;
    }
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if (player) {
        player->moveto(event->pos());
        if (!ball->launched) ball->setPos(player->x() + (player->w - ball->w)/2, player->y() - ball->h);
    }
}

void Game::addBricks()
{
    int n,x,s;
    QPixmap *pmap = new QPixmap(":/images/grey");
    n = gwidth/pmap->width();
    s = (gwidth - n * pmap->width() - (n-1)*3)/2;
    for (int i=0; i<n; i++) {
        Brick *b = new Brick(pmap);
        x = s + i*3 + b->w*i;
        b->setPos(x,10);
        b->tp = Brick::Grey;
        scene->addItem(b);
    }
    pmap = new QPixmap(":/images/purple");
    for (int i=0; i<n; i++) {
        Brick *b = new Brick(pmap);
        x = s + i*3 + b->w*i;
        b->setPos(x,10+b->h+5);
        b->tp = Brick::Purple;
        scene->addItem(b);
    }
    pmap = new QPixmap(":/images/red");
    for (int i=0; i<n; i++) {
        Brick *b = new Brick(pmap);
        x = s + i*3 + b->w*i;
        b->setPos(x,10+2*(b->h)+2*5);
        b->tp = Brick::Red;
        scene->addItem(b);
    }
    pmap = new QPixmap(":/images/blue");
    for (int i=0; i<n; i++) {
        Brick *b = new Brick(pmap);
        x = s + i*3 + b->w*i;
        b->setPos(x,10+3*(b->h)+3*5);
        b->tp = Brick::Blue;
        scene->addItem(b);
    }
    pmap = new QPixmap(":/images/green");
    for (int i=0; i<n; i++) {
        Brick *b = new Brick(pmap);
        x = s + i*3 + b->w*i;
        b->setPos(x,10+4*(b->h)+4*5);
        b->tp = Brick::Green;
        scene->addItem(b);
    }
    pmap = new QPixmap(":/images/yellow");
    for (int i=0; i<n; i++) {
        Brick *b = new Brick(pmap);
        x = s + i*3 + b->w*i;
        b->setPos(x,10+5*(b->h)+5*5);
        b->tp = Brick::Yellow;
        scene->addItem(b);
    }
}


void Game::playerLose()
{
    // PLAYER LOSE ACTIONS
    lives--;
    showHud();

    if(lives == 0) gameOver();
    else loseball->play();

    if (ball) {
        ball->setPos(player->x() + (player->w - ball->w)/2, player->y() - ball->h);
    }
}

void Game::showHud()
{
    if (scene->items().contains(txtHud)) scene->removeItem(txtHud);
    txtHud->setPlainText("LIVES: "+QString::number(lives)+"   POINTS: "+QString::number(points));
    txtHud->setPos((gwidth - (0.68 * txtHud->font().pointSize()*txtHud->toPlainText().length()))/2,gheight-40);
    scene->addItem(txtHud);
}

void Game::setPoints(int bricktype)
{
    // here you can place a switch{} to assign different point for each brick type (see Brick::tps for types)
    points+=bricktype*100;
    showHud();
}

void Game::gameOver()
{
    scene->removeItem(player);
    scene->removeItem(ball);
    QGraphicsTextItem *text = new QGraphicsTextItem();
    text->setDefaultTextColor(Qt::red);
    text->setFont(myfont36);
    qDebug() << text->font().pointSize();
    QString g = "GAME OVER";
    text->setPlainText(g);
    text->setPos((gwidth - (0.68 * text->font().pointSize()*g.length()))/2,(gheight-text->font().pointSize())/2);
    scene->addItem(text);
}



void Game::playerWin()
{
    // PLAYER WIN ACTIONS
    scene->removeItem(player);
    scene->removeItem(ball);
    QGraphicsTextItem *text = new QGraphicsTextItem();
    text->setDefaultTextColor(Qt::blue);
    text->setFont(myfont36);
    QString g = "GAME OVER - YOU WIN";
    text->setPlainText(g);
    text->setPos((gwidth - (0.68 * text->font().pointSize()*g.length()))/2,(gheight-text->font().pointSize())/2);
    scene->addItem(text);
}

