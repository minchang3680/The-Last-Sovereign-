#pragma once

#include "Resources.h"
#include <iostream>
#include <string>

class TurnSystem {
private:
    Resources* currentPlayer;
    Resources player1;
    Resources player2;

    int turn;
    int scienceResearchCount;
    int magicResearchCount;
    int ringPosition = 0;
    int ringPosition1 = 0;
    int ringPosition2 = 0;
    int currentTurn = 1;

public:
    TurnSystem();
    void start();
    void playTurn();
    void swapCurrentPlayer();
    bool checkEnd();
    Resources* getOpponentPlayer();
    Resources& getOpponent(Resources& player);
    int getCurrentTurn() const;

    bool debugSkipToRingTest = false;
};
