#pragma once

#pragma once
#include "Resources.h"
#include <string>
using namespace std;

class Event {
private:
    string name;       // �̺�Ʈ �̸�
    string description;  // �̺�Ʈ ����
    string optionA;    // ������ A
    string optionB;    // ������ B

    int economyChangeA, militaryChangeA, moraleChangeA, religionChangeA, scienceOrMagicChangeA;
    int economyChangeB, militaryChangeB, moraleChangeB, religionChangeB, scienceOrMagicChangeB;

public:
    Event(string n, string desc, string optA, string optB,
        int ecoA, int milA, int morA, int relA, int sciMagA,
        int ecoB, int milB, int morB, int relB, int sciMagB);

    void displayEvent() const;  // �̺�Ʈ ǥ��
    void applyEvent(Resources& player, char choice); // ������ �ɼ� ����
    static Event generateRandomEvent();  // ���� �̺�Ʈ ����
};
