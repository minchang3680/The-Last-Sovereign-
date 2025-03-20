#pragma once

#include "Resources.h"
#include <string>
using namespace std;

class Event {
private:
    string name;    // 이벤트 이름
    string description;  // 이벤트 설명
    int economyChange;
    int militaryChange;
    int moraleChange;
    int religionChange;
    int scienceOrMagicChange;

public:
    Event(string n, string desc, int eco, int mil, int mor, int rel, int sciMag);
    void applyEvent(Resources& player); // 플레이어에게 이벤트 적용
    void displayEvent(const string& nationType) const;  // 이벤트 내용 출력
    static Event generateRandomEvent(); // 랜덤 이벤트 생성
};
