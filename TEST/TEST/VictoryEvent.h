// VictoryEvent.h
#pragma once
#include "Resources.h"
#include <iostream>
using namespace std;

class VictoryEvent {
public:
    // ����ź or �����̾� �¸� ����
    static void executeNuclearVictory(const Resources& winner, const Resources& loser);

    // ������� �¸� ����
    static void executeRingVictory(const Resources& winner, const Resources& loser);
};

