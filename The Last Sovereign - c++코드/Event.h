#pragma once
#include "Resources.h"
#include <string>
using namespace std;

class Event {
private:
    string name;
    string description;
    string optionA;
    string optionB;
    string resultMessageA;  // ���� A �� ��� �޽���
    string resultMessageB;  // ���� B �� ��� �޽���

    int economyChangeA, militaryChangeA, moraleChangeA, religionChangeA, scienceOrMagicChangeA;
    int economyChangeB, militaryChangeB, moraleChangeB, religionChangeB, scienceOrMagicChangeB;

public:
    Event(string n, string desc, string optA, string optB, string resA, string resB,
        int ecoA, int milA, int morA, int relA, int sciMagA,
        int ecoB, int milB, int morB, int relB, int sciMagB);

    void displayEvent() const;
    void applyEvent(Resources& player, char choice);
    static Event generateRandomEvent();
};

