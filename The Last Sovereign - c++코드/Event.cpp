#include "Event.h"
#include <iostream>
#include <vector>
#include <cstdlib>  // 랜덤 값 생성
#include <ctime>

using namespace std;

// 🔹 생성자: 이벤트의 기본 정보 설정
Event::Event(string n, string desc, string optA, string optB, string resA, string resB,
    int ecoA, int milA, int morA, int relA, int sciMagA,
    int ecoB, int milB, int morB, int relB, int sciMagB)
    : name(n), description(desc), optionA(optA), optionB(optB),
    resultMessageA(resA), resultMessageB(resB),
    economyChangeA(ecoA), militaryChangeA(milA), moraleChangeA(morA), religionChangeA(relA), scienceOrMagicChangeA(sciMagA),
    economyChangeB(ecoB), militaryChangeB(milB), moraleChangeB(morB), religionChangeB(relB), scienceOrMagicChangeB(sciMagB) {
}


void Event::displayEvent() const {
    cout << "\n[이벤트 발생] " << name << endl;
    cout << description << endl;
    cout << "1. " << optionA << endl;
    cout << "2. " << optionB << endl;
}


void Event::applyEvent(Resources& player, char choice) {
    if (choice == '1') {
        player.modify(economyChangeA, militaryChangeA, moraleChangeA, religionChangeA, scienceOrMagicChangeA);
        cout << "\n🟢 " << resultMessageA << "\n" << endl;
    }
    else {
        player.modify(economyChangeB, militaryChangeB, moraleChangeB, religionChangeB, scienceOrMagicChangeB);
        cout << "\n🔵 " << resultMessageB << "\n" << endl;
    }
}

Event Event::generateRandomEvent() {
    vector<Event> eventList = {
        Event("세금 정책", "세금을 조정할 기회입니다.",
              "세금 인상 (경제 +10, 민심 -5)", "세금 감면 (경제 -10, 민심 +5)",
              "세금을 인상하여 국가 재정이 안정됩니다. 하지만 국민들은 불만을 느낍니다.",
              "세금을 감면하여 국민들이 기뻐합니다. 하지만 국가 재정이 악화됩니다.",
              10, 0, -5, 0, 0,  -10, 0, 5, 0, 0),

        Event("군사 훈련", "군사력을 강화할 것인가?",
              "강력한 훈련 (군사 +10, 경제 -5)", "훈련 완화 (군사 -5, 경제 +10)",
              "군사 훈련을 강하게 진행하여 군사력이 상승했습니다.",
              "훈련을 완화하여 병사들의 피로도가 줄어들었지만 군사력이 약화되었습니다.",
              -5, 10, 0, 0, 0,   10, -5, 0, 0, 0),

        Event("종교 개혁", "종교적 개혁을 단행합니다.",
              "종교 강화 (종교 +10, 민심 -5)", "종교 자유화 (종교 -5, 민심 +10)",
              "종교를 강화하여 신자들이 기뻐하지만, 일부 시민들은 반발합니다.",
              "종교 자유화를 선언하여 시민들이 만족하지만, 성직자들은 불만을 표합니다.",
              0, 0, -5, 10, 0,   0, 0, 10, -5, 0)
    };

    int randomIndex = rand() % eventList.size();
    return eventList[randomIndex];
}
