// VictoryCondition.h
#pragma once
#include "Resources.h"  // 필요 시

class VictoryCondition {
public:
    // 핵폭탄 / 헬파이어 조건 달성 여부 판단
    static bool checkVictoryByNuke(const Resources& player);

    // 핵/헬파이어로 승리
    static void declareNukeVictory(const Resources& winner, const Resources& loser);

    // 절대반지로 승리
    static void declareRingVictory(const Resources& winner, const Resources& loser);

    // 상대 패배로 인한 일반 승리
    static void declareStandardVictory(const Resources& winner, const Resources& loser);

    // 절대반지 승리 조건 (75칸 도달)
    static bool checkVictoryByRing(int ringPosition);

    // 일반 승리: 상대가 패배 조건을 만족했는지 확인
    static bool checkVictoryByDefeatOfOpponent(const Resources& opponent);

    static bool canTriggerNukeEvent(const Resources& player);
};
