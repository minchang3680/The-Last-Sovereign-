#include "Event.h"
#include <iostream>
#include <vector>
#include <cstdlib>  // 랜덤 값 생성
#include <ctime>

using namespace std;

// 🔹 생성자: 이벤트의 기본 정보 설정
Event::Event(string n, string desc, string optA, string optB,
    int ecoA, int milA, int morA, int relA, int sciMagA,
    int ecoB, int milB, int morB, int relB, int sciMagB)
    : name(n), description(desc), optionA(optA), optionB(optB),
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
    }
    else {
        player.modify(economyChangeB, militaryChangeB, moraleChangeB, religionChangeB, scienceOrMagicChangeB);
    }
}

Event Event::generateRandomEvent() {
    vector<Event> eventList = {
        Event("세금 정책", "세금을 조정할 기회입니다.",
              "세금 인상 (경제 +10, 민심 -5)", "세금 감면 (경제 -10, 민심 +5)",
              10, 0, -5, 0, 0,  -10, 0, 5, 0, 0),

        Event("군사 훈련", "군사력을 강화할 것인가?",
              "강력한 훈련 (군사 +10, 경제 -5)", "훈련 완화 (군사 -5, 경제 +10)",
              -5, 10, 0, 0, 0,   10, -5, 0, 0, 0),

        Event("종교 개혁", "종교적 개혁을 단행합니다.",
              "종교 강화 (종교 +10, 민심 -5)", "종교 자유화 (종교 -5, 민심 +10)",
              0, 0, -5, 10, 0,   0, 0, 10, -5, 0)
    };

    int randomIndex = rand() % eventList.size();
    return eventList[randomIndex];
}