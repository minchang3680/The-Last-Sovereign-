#include "Resources.h"
#include <iostream>
#include <cstdlib>  // 난수 생성용
#include <ctime>    // 시간 기반 시드 설정

using namespace std;

// 🔹 기본 생성자 구현
Resources::Resources(string nation) {
    srand(static_cast<unsigned int>(time(0))); // 난수 생성 시드 설정
    nationType = nation;

    economy = 50;
    military = 50;
    morale = 50;
    religion = 50;
    scienceOrMagic = 50;

    maxEconomy = 100;
    maxMilitary = 100;
    maxMorale = 100;
    maxReligion = 100;
    maxScienOrMagic = 100;

    for (int i = 0; i < 5; i++) {
        turnAtMax[i] = 0;
    }
}


bool Resources::checkGameOver(Resources& opponent) {
    string loser = nationType;       // 현재 플레이어 (패배한 국가)
    string winner = opponent.getNationType(); // 상대 플레이어 (승리한 국가)

    // 🔹 1. 자원이 0 이하이면 즉시 패배
    if (economy <= 0) {
        cout << loser << " 왕국이 패배했습니다! (국가 경제 체제가 붕괴되었습니다!)" << endl;
        cout << winner << " 왕국이 승리했습니다!" << endl;  // ✅ 승리한 국가 출력
        return true;
    }
    if (military <= 0) {
        cout << loser << " 왕국이 패배했습니다! (국가의 군사력이 완전히 무너졌습니다!)" << endl;
        cout << winner << " 왕국이 승리했습니다!" << endl;
        return true;
    }
    if (morale <= 0) {
        cout << loser << " 왕국이 패배했습니다! (국민들의 신뢰를 완전히 잃었습니다!)" << endl;
        cout << winner << " 왕국이 승리했습니다!" << endl;
        return true;
    }
    if (religion <= 0) {
        cout << loser << " 왕국이 패배했습니다! (국가의 종교 기반이 완전히 사라졌습니다!)" << endl;
        cout << winner << " 왕국이 승리했습니다!" << endl;
        return true;
    }
    if (scienceOrMagic <= 0) {
        if (nationType == "Science") {
            cout << "과학 왕국이 패배했습니다! (과학이 몰락하여 지식이 사라졌습니다!)" << endl;
            cout << "마법 왕국이 승리했습니다!" << endl;
        }
        else {
            cout << "마법 왕국이 패배했습니다! (마법이 사라져 왕국이 무너졌습니다!)" << endl;
            cout << "과학 왕국이 승리했습니다!" << endl;
        }
        return true;
    }

    // 🔹 2. 특정 자원이 100% 이상 상태가 2턴 이상 지속되면 패배
    for (int i = 0; i < 5; i++) {
        if (turnAtMax[i] >= 2) {
            switch (i) {
            case 0:
                cout << loser << " 왕국이 패배했습니다! (극단적 인플레이션으로 인해 국가가 붕괴되었습니다!)" << endl;
                break;
            case 1:
                cout << loser << " 왕국이 패배했습니다! (군사 독재가 발생하여 왕국이 무너졌습니다!)" << endl;
                break;
            case 2:
                cout << loser << " 왕국이 패배했습니다! (민심이 너무 높아 정부를 무시하는 폭동이 발생했습니다!)" << endl;
                break;
            case 3:
                cout << loser << " 왕국이 패배했습니다! (종교적 광신이 너무 강해 국가 운영이 불가능해졌습니다!)" << endl;
                break;
            case 4:
                if (nationType == "Science") {
                    cout << "과학 왕국이 패배했습니다! (과학이 너무 발전하여 인공지능이 왕국을 지배했습니다!)" << endl;
                    cout << "마법 왕국이 승리했습니다!" << endl;
                }
                else {
                    cout << "마법 왕국이 패배했습니다! (마법이 너무 강해져 왕국이 현실을 초월해 사라졌습니다!)" << endl;
                    cout << "과학 왕국이 승리했습니다!" << endl;
                }
                break;
            }
            return true;
        }
    }

    return false; // 게임 계속 진행
}

// 100% 초과한 턴 수를 체크
void Resources::trackMaxResourceTurns() {
    for (int i = 0; i < 5; i++) {
        int currentResource;

        // 현재 자원의 값을 가져오기
        switch (i) {
        case 0: currentResource = economy; break;
        case 1: currentResource = military; break;
        case 2: currentResource = morale; break;
        case 3: currentResource = religion; break;
        case 4: currentResource = scienceOrMagic; break;
        }

        // 각 자원의 100% 초과 상태를 개별적으로 관리
        if (currentResource >= 100) {
            turnAtMax[i]++;  // 해당 자원의 초과된 턴 수 증가
        }
        else if (turnAtMax[i] > 0) {
            // 해당 자원이 100% 미만이 되면 그 자원의 초과 턴 수만 초기화
            turnAtMax[i] = 0;
        }
    }
}

void Resources::modify(int eco, int mil, int mor, int rel, int sciMag) {
    economy += eco;       // 경제 자원 증가 또는 감소
    military += mil;      // 군사력 증가 또는 감소
    morale += mor;        // 민심 증가 또는 감소
    religion += rel;      // 종교 증가 또는 감소
    scienceOrMagic += sciMag; // 과학/마법 증가 또는 감소
}

void Resources::display() {
    cout << "=== 현재 자원 === " << endl;
    cout << "경제: " << economy << " | "
        << "군사력: " << military << " | "
        << "민심: " << morale << " | "
        << "종교: " << religion << " | ";

    // ✅ 국가 타입에 따라 과학 또는 마법 출력
    if (nationType == "Science") {
        cout << "과학: " << scienceOrMagic << endl;
    }
    else {
        cout << "마법: " << scienceOrMagic << endl;
    }
}


// ✅ 국가 타입을 반환하는 함수 (public)
string Resources::getNationType() const {
    return nationType;
}

int Resources::getMilitary() const {
    return military;
}

void Resources::incrementResearch() {
    if (nationType == "Science") {
        scienceResearchCount++;
    }
    else {
        magicResearchCount++;
    }
}

void Resources::completeMilitaryUpgrade() {
    militaryUpgradeCompleted = true;
}

int Resources::getScienceResearchCount() const {
    return scienceResearchCount;
}

int Resources::getMagicResearchCount() const {
    return magicResearchCount;
}

bool Resources::isMilitaryUpgraded() const {
    return militaryUpgradeCompleted;
}









