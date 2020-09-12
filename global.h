/*
 * QArkanoid
 * Simple "Arkanoid" type game, based on QT libraries
 * (c) 2020 by Felice Murolo, all rights reserved
 * licensed under GPL3, see LICENSE file
 * email: linuxboy@giove.tk
 * Location: Salerno, Italia
 *
*/
#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>

extern int gwidth;
extern int gheight;
extern QString prgname;
extern QString version;
extern QString copyright;


class global
{
public:
    global();
};

#endif // GLOBAL_H
