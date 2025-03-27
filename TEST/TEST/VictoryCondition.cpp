// VictoryCondition.cpp
#include "VictoryCondition.h"
#include "VictoryEvent.h"


bool VictoryCondition::checkVictoryByNuke(const Resources& player) {
    // ��¥ �߻縦 �ߴ��� ���θ� Ȯ�� (�ܼ� üũ �Լ�)
    return player.hasLaunchedNuke();
}

bool VictoryCondition::checkVictoryByRing(int ringPosition) {
    return ringPosition >= 75;
}

bool VictoryCondition::checkVictoryByDefeatOfOpponent(const Resources& opponent) {
    // ��밡 �ڿ� 0 �Ǵ� 100% �̻� 2�� ������ �й��� ���
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
    cout << loser.getNationType() << " �ձ��� �й��Ͽ����ϴ�." << endl;
    cout << winner.getNationType() << " �ձ��� �¸�!" << endl;
    exit(0);
}

bool VictoryCondition::canTriggerNukeEvent(const Resources& player) {
    if (!player.isMilitaryUpgraded()) return false;
    if (player.getResearchLevel() < 4) return false;
    if (player.getMilitary() < 70 || player.getEconomy() < 70) return false;
    if (player.hasLaunchedNuke()) return false;
    return true;
}


