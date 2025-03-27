#pragma once
#ifndef GAME_H
#define GAME_H

#include "Resources.h"
#include "Event.h"
#include <iostream>

using namespace std;

class Game {
private:
    Resources playerResources;
    int turn;
public:
    Game(string nation);
    void start();
    void playTurn();
    bool checkEnd();
};

#endif

