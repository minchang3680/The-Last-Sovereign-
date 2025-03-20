#pragma once

#include "Resources.h"
#include <string>
using namespace std;

class Event {
private:
    string name;    // �̺�Ʈ �̸�
    string description;  // �̺�Ʈ ����
    int economyChange;
    int militaryChange;
    int moraleChange;
    int religionChange;
    int scienceOrMagicChange;

public:
    Event(string n, string desc, int eco, int mil, int mor, int rel, int sciMag);
    void applyEvent(Resources& player); // �÷��̾�� �̺�Ʈ ����
    void displayEvent(const string& nationType) const;  // �̺�Ʈ ���� ���
    static Event generateRandomEvent(); // ���� �̺�Ʈ ����
};
