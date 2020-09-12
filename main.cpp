/*
 * QArkanoid
 * Simple "Arkanoid" type game, based on QT libraries
 * (c) 2020 by Felice Murolo, all rights reserved
 * licensed under GPL3, see LICENSE file
 * email: linuxboy@giove.tk
 * Location: Salerno, Italia
 *
*/

#include <QApplication>
#include "game.h"

Game *game=nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();

    return a.exec();
}
