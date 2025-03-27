// DefeatCondition.cpp

#include "DefeatCondition.h"
#include "Resources.h"
#include "VictoryCondition.h"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

// ✅ 자원 0일 경우 패배
bool DefeatCondition::checkResourceZero(const Resources& player) {
    return (player.getEconomy() <= 0 || player.getMilitary() <= 0 ||
        player.getMorale() <= 0 || player.getReligion() <= 0 ||
        player.getScienceOrMagic() <= 0);
}

// ✅ 자원이 100 이상 상태를 3턴 이상 유지할 경우 패배
bool DefeatCondition::checkResourceOverflowFail(const Resources& player) {
    const vector<int>& turns = player.getTurnAtMax();

    int current[5] = {
        player.getEconomy(),
        player.getMilitary(),
        player.getMorale(),
        player.getReligion(),
        player.getScienceOrMagic()
    };

    int maxes[5] = {
        player.getMaxEconomy(),
        player.getMaxMilitary(),
        player.getMaxMorale(),
        player.getMaxReligion(),
        player.getMaxScienceOrMagic()
    };

    for (int i = 0; i < 5; ++i) {
        if (current[i] >= maxes[i] && turns[i] >= 3 && player.hasRecoveryEventTriggered(i)) {
            return true;
        }
    }

    return false;
}




// ✅ 절대 반지로 인한 패배
bool DefeatCondition::checkDefeatByRing(int opponentRingPosition) {
    return opponentRingPosition >= 75;
}

void DefeatCondition::declareResourceZeroDefeat(const Resources& loser, const Resources& winner) {
    if (loser.getEconomy() <= 0) {
        cout << loser.getNationType() << " 왕국의 경제 파탄으로 인해 국가가 붕괴되었습니다." << endl;
    }
    else if (loser.getMilitary() <= 0) {
        cout << loser.getNationType() << " 왕국의 군사력 붕괴로 인해 침략당하고 멸망하였습니다." << endl;
    }
    else if (loser.getMorale() <= 0) {
        cout << loser.getNationType() << " 왕국의 민심이 무너져 내전이 발생하고 멸망하였습니다." << endl;
    }
    else if (loser.getReligion() <= 0) {
        cout << loser.getNationType() << " 왕국의 종교 기반이 붕괴되어 통제력을 잃고 멸망하였습니다." << endl;
    }
    else if (loser.getScienceOrMagic() <= 0) {
        if (loser.getNationType() == "Science") {
            cout << "과학 왕국이 과학의 몰락으로 인해 기술 문명이 붕괴되었습니다." << endl;
        }
        else {
            cout << "마법 왕국이 마법의 소멸로 인해 왕국이 무너졌습니다." << endl;
        }
    }
    cout << winner.getNationType() << " 왕국의 승리!" << endl;
    exit(0);
}

void DefeatCondition::declareOverflowDefeat(const Resources& loser, const Resources& winner) {
    const vector<int>& turns = loser.getTurnAtMax();  // ✅ vector 사용
    string kingdom = loser.getNationType();
    for (int i = 0; i < 5; ++i) {
        if (turns[i] >= 3) {
            string message;
            switch (i) {
            case 0: message = "극단적인 인플레이션으로 인해 국가가 붕괴되었습니다."; break;
            case 1: message = "군사 독재가 발생하여 반란으로 멸망하였습니다."; break;
            case 2: message = "과도한 민심으로 정부가 마비되고 멸망하였습니다."; break;
            case 3: message = "광신적 종교 폭주로 왕국이 무너졌습니다."; break;
            case 4:
                if (kingdom == "Science")
                    message = "인공지능의 반란으로 왕국이 지배당하고 멸망하였습니다.";
                else
                    message = "마법이 폭주하여 현실이 왜곡되고 왕국이 소멸하였습니다.";
                break;
            }
            cout << kingdom << " 왕국이 " << message << endl;
            cout << winner.getNationType() << " 왕국의 승리!" << endl;
            exit(0);
        }
    }
}

void DefeatCondition::declareRingDefeat(const Resources& loser, const Resources& winner) {
    cout << winner.getNationType() << " 왕국이 절대 반지를 획득하였습니다!" << endl;
    cout << loser.getNationType() << " 왕국은 절대 복종을 할 수밖에 없게 되었습니다." << endl;
    cout << winner.getNationType() << " 왕국의 승리!" << endl;
    exit(0);
}

void DefeatCondition::declareNukeDefeat(const Resources& loser, const Resources& winner) {
    if (winner.getNationType() == "Science") {
        cout << "과학 왕국이 핵폭탄을 발사하였습니다!" << endl;                            
        cout << "마법 왕국이 전멸하였습니다." << endl;
    }
    else {
        cout << "마법 왕국이 헬파이어를 시전하였습니다!" << endl;
        cout << "과학 왕국이 소멸하였습니다." << endl;
    }
    cout << winner.getNationType() << " 왕국의 승리!" << endl;
    exit(0);
}

int DefeatCondition::getOverflowTarget(const Resources& player) {
    // 각 자원 값을 배열에 저장
    int values[5] = {
        player.getEconomy(),
        player.getMilitary(),
        player.getMorale(),
        player.getReligion(),
        player.getScienceOrMagic()
    };

    // 0부터 4까지 순회하면서 100 이상인 자원을 찾는다
    for (int i = 0; i < 5; i++) {
        if (values[i] >= 100) {
            return i; // 해당 자원의 index 반환
        }
    }

    return -1; // 회생 대상이 없음
}

int DefeatCondition::getImmediateOverflowTarget(const Resources& player) {
    int values[5] = {
        player.getEconomy(),
        player.getMilitary(),
        player.getMorale(),
        player.getReligion(),
        player.getScienceOrMagic()
    };

    for (int i = 0; i < 5; i++) {
        if (values[i] >= 100) {
            return i; // 해당 자원의 인덱스 반환
        }
    }

    return -1; // 즉시 회생 대상 없음
}





