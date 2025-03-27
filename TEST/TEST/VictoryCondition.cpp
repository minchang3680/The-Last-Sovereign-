// VictoryCondition.cpp
#include "VictoryCondition.h"
#include "VictoryEvent.h"


bool VictoryCondition::checkVictoryByNuke(const Resources& player) {
    // 진짜 발사를 했는지 여부만 확인 (단순 체크 함수)
    return player.hasLaunchedNuke();
}

bool VictoryCondition::checkVictoryByRing(int ringPosition) {
    return ringPosition >= 75;
}

bool VictoryCondition::checkVictoryByDefeatOfOpponent(const Resources& opponent) {
    // 상대가 자원 0 또는 100% 이상 2턴 유지로 패배한 경우
    const vector<int>& turnAtMax = opponent.getTurnAtMax();

    for (int i = 0; i < 5; i++) {
        if (turnAtMax[i] >= 3) return true;
    }

    if (opponent.getEconomy() <= 0 || opponent.getMilitary() <= 0 || opponent.getMorale() <= 0 ||
        opponent.getReligion() <= 0 || opponent.getScienceOrMagic() <= 0) {
        return true;
    }

    return false;
}

void VictoryCondition::declareNukeVictory(const Resources& winner, const Resources& loser) {
    VictoryEvent::executeNuclearVictory(winner, loser);
}

void VictoryCondition::declareRingVictory(const Resources& winner, const Resources& loser) {
    VictoryEvent::executeRingVictory(winner, loser);
    exit(0);
}

void VictoryCondition::declareStandardVictory(const Resources& winner, const Resources& loser) {
    cout << loser.getNationType() << " 왕국이 패배하였습니다." << endl;
    cout << winner.getNationType() << " 왕국의 승리!" << endl;
    exit(0);
}

bool VictoryCondition::canTriggerNukeEvent(const Resources& player) {
    if (!player.isMilitaryUpgraded()) return false;
    if (player.getResearchLevel() < 4) return false;
    if (player.getMilitary() < 70 || player.getEconomy() < 70) return false;
    if (player.hasLaunchedNuke()) return false;
    return true;
}


