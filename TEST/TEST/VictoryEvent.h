// VictoryEvent.h
#pragma once
#include "Resources.h"
#include <iostream>
using namespace std;

class VictoryEvent {
public:
    // ÇÙÆøÅº or ÇïÆÄÀÌ¾î ½Â¸® ¿¬Ãâ
    static void executeNuclearVictory(const Resources& winner, const Resources& loser);

    // Àı´ë¹İÁö ½Â¸® ¿¬Ãâ
    static void executeRingVictory(const Resources& winner, const Resources& loser);
};

