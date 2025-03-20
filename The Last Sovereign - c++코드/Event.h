#pragma once

#pragma once
#include "Resources.h"
#include <string>
using namespace std;

class Event {
private:
    string name;       // 이벤트 이름
    string description;  // 이벤트 설명
    string optionA;    // 선택지 A
    string optionB;    // 선택지 B

    int economyChangeA, militaryChangeA, moraleChangeA, religionChangeA, scienceOrMagicChangeA;
    int economyChangeB, militaryChangeB, moraleChangeB, religionChangeB, scienceOrMagicChangeB;

public:
    Event(string n, string desc, string optA, string optB,
        int ecoA, int milA, int morA, int relA, int sciMagA,
        int ecoB, int milB, int morB, int relB, int sciMagB);

    void displayEvent() const;  // 이벤트 표시
    void applyEvent(Resources& player, char choice); // 선택한 옵션 적용
    static Event generateRandomEvent();  // 랜덤 이벤트 생성
};
