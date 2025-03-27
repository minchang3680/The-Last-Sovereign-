#pragma once
#include "Resources.h"
#include <string>
using namespace std;

// ✅ enum 선언을 클래스 바깥 또는 맨 위로 이동
enum class PressureEffectType {
    NONE,
    DECREASE,
    BLOCK,
    SUPPORT
};

class Event {
private:
    string title;
    string description;
    string optionA;
    string optionB;
    string resultMessageA;
    string resultMessageB;

    int economyChangeA, militaryChangeA, moraleChangeA, religionChangeA, scienceOrMagicChangeA;
    int economyChangeB, militaryChangeB, moraleChangeB, religionChangeB, scienceOrMagicChangeB;

    string eventType = "일반 이벤트";

public:
    Event();

    Event(string n, string desc,
        string optA, string optB,
        string resA, string resB,
        int ecoA, int milA, int morA, int relA, int sciMagA,
        int ecoB, int milB, int morB, int relB, int sciMagB,
        bool recovery,
        string type,
        PressureEffectType effect = PressureEffectType::NONE,
        int affectedIndex = -1);

    string getType() const;
    void displayEvent() const;
    void applyEvent(Resources& player, char choice, int& ringPosition, int& opponentRingPosition);

    static Event generateRandomEvent(const Resources& player, bool allowUpgrade = true, bool allowRecovery = true);
    static Event generateBigEvent();
    static Event generateUpgradeEvent(const Resources& player);
    static Event generateRecoveryEvent(const Resources& player, int stage);
    static Event generateNukeEvent(const Resources& player);
    static Event generateResearchEvent(const Resources& player);
    static Event generateRingZoneEvent(const Resources& player);

    static Event generatePressureEvent(const Resources& player);

    string getTitle() const;

    bool isRecovery = false;
    string type;

    // ✅ 압박 이벤트 세부 정보
    PressureEffectType pressureEffect = PressureEffectType::NONE;
    int affectedResourceIndex = -1;

    string getDescription() const;

};