// Event.cpp

#include "Event.h"
#include "Resources.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>



using namespace std;

extern Resources player1;
extern Resources player2;

Resources& getOpponent(Resources& player) {
    return (&player == &player1) ? player2 : player1;
}

Event::Event()
    : title(""), description(""), optionA(""), optionB(""),
    resultMessageA(""), resultMessageB(""),
    economyChangeA(0), militaryChangeA(0), moraleChangeA(0), religionChangeA(0), scienceOrMagicChangeA(0),
    economyChangeB(0), militaryChangeB(0), moraleChangeB(0), religionChangeB(0), scienceOrMagicChangeB(0) {
}

Event::Event(string n, string desc,
    string optA, string optB,
    string resA, string resB,
    int ecoA, int milA, int morA, int relA, int sciMagA,
    int ecoB, int milB, int morB, int relB, int sciMagB,
    bool recovery,
    string type,
    PressureEffectType effect,
    int affectedIndex)
    : title(n), description(desc),
    optionA(optA), optionB(optB),
    resultMessageA(resA), resultMessageB(resB),
    economyChangeA(ecoA), militaryChangeA(milA), moraleChangeA(morA),
    religionChangeA(relA), scienceOrMagicChangeA(sciMagA),
    economyChangeB(ecoB), militaryChangeB(milB), moraleChangeB(morB),
    religionChangeB(relB), scienceOrMagicChangeB(sciMagB),
    isRecovery(recovery), eventType(type),
    pressureEffect(effect), affectedResourceIndex(affectedIndex)
{
}



void Event::displayEvent() const {
    cout << "\n[" << eventType << "]" << endl;     // ✅ 이벤트 종류 출력
    cout << "[" << title << "] " << description << endl;  // ✅ 이벤트 이름 + 설명
    cout << "1. " << optionA << endl;
    cout << "2. " << optionB << endl;
}


void Event::applyEvent(Resources& player, char choice, int& ringPosition, int& opponentRingPosition) {
    // 기존 자원 값 저장 (필요 시 활용 가능)
    int before[5] = {
        player.getEconomy(),
        player.getMilitary(),
        player.getMorale(),
        player.getReligion(),
        player.getScienceOrMagic()
    };

    Resources& opponent = getOpponent(player);  // 상대 자원 참조

    // 선택 A: 자원 변화 (내 자원과 상대 자원 구분)
    if (choice == '1') {
        int playerChanges[5] = { economyChangeA, militaryChangeA, moraleChangeA, religionChangeA, scienceOrMagicChangeA };
        int opponentChanges[5] = { 0, 0, 0, 0, 0 };

        // 압박 이벤트인 경우 상대 자원 수정
        if (eventType == "압박 이벤트") {
            switch (pressureEffect) {
            case PressureEffectType::DECREASE:
                opponentChanges[affectedResourceIndex] = -10;  // 상대 자원 감소
                break;
            case PressureEffectType::BLOCK:
                opponent.blockResource(affectedResourceIndex); // 자원 차단
                break;
            case PressureEffectType::SUPPORT:
                playerChanges[affectedResourceIndex] = -10;    // 내 자원 감소
                opponentChanges[affectedResourceIndex] = 10;   // 상대 자원 증가
                break;
            default:
                break;
            }
        }

        // 내 자원 변경
        player.modify(playerChanges[0], playerChanges[1], playerChanges[2], playerChanges[3], playerChanges[4]);
        // 상대 자원 변경
        opponent.modify(opponentChanges[0], opponentChanges[1], opponentChanges[2], opponentChanges[3], opponentChanges[4]);

        // 선택 A에 대한 메시지 출력
        cout << "자원 변경 사항 (내 자원): 경제: " << playerChanges[0] << ", 군사: " << playerChanges[1] << ", 민심: " << playerChanges[2]
            << ", 종교: " << playerChanges[3] << ", 과학/마법: " << playerChanges[4] << endl;

        cout << "자원 변경 사항 (상대 자원): 경제: " << opponentChanges[0] << ", 군사: " << opponentChanges[1] << ", 민심: " << opponentChanges[2]
            << ", 종교: " << opponentChanges[3] << ", 과학/마법: " << opponentChanges[4] << endl;
    }
    // 선택 B: 자원 변화
    else {
        int playerChanges[5] = { economyChangeB, militaryChangeB, moraleChangeB, religionChangeB, scienceOrMagicChangeB };
        int opponentChanges[5] = { 0, 0, 0, 0, 0 };

        player.modify(playerChanges[0], playerChanges[1], playerChanges[2], playerChanges[3], playerChanges[4]);
        opponent.modify(opponentChanges[0], opponentChanges[1], opponentChanges[2], opponentChanges[3], opponentChanges[4]);

        // 선택 B에 대한 메시지 출력
        cout << "자원 변경 사항 (내 자원): 경제: " << playerChanges[0] << ", 군사: " << playerChanges[1] << ", 민심: " << playerChanges[2]
            << ", 종교: " << playerChanges[3] << ", 과학/마법: " << playerChanges[4] << endl;
    }

    // 핵/헬파이어 이벤트는 무조건 발사 처리
    if (eventType == "핵/헬파이어 이벤트") {
        player.launchNuke();
    }

    // 반지 이벤트 처리
    if (eventType == "반지 이벤트") {
        if (getTitle().find("지도의 발견") != string::npos && choice == '1') {
            ringPosition += 2;
            cout << "(추가 이동) 절대반지를 향해 2칸 더 이동합니다! (현재 위치: " << ringPosition << ")\n";
        }
        else if (getTitle().find("폭풍 소환") != string::npos && choice == '1') {
            opponentRingPosition = max(0, opponentRingPosition - 1);
            cout << "(방해 성공) 상대방의 반지 진행도를 1칸 늦췄습니다! (상대 현재 위치: " << opponentRingPosition << ")\n";
        }
    }
}


Event Event::generateRandomEvent(const Resources& player, bool allowUpgrade, bool allowRecovery) {
    vector<Event> eventList = {
        Event("세금 정책", "세금을 조정할 기회입니다.",
          "세금 인상 (경제 +10, 민심 -5)", "세금 감면 (경제 -10, 민심 +5)",
          "세금을 인상하여 국가 재정이 안정됩니다. 하지만 국민들은 불만을 느낍니다.",
          "세금을 감면하여 국민들이 기뻐합니다. 하지만 국가 재정이 악화됩니다.",
          10, 0, -5, 0, 0,
          -10, 0, 5, 0, 0, false, "일반 이벤트"),

          // 경제 중심 이벤트
          Event("산업 진흥 정책", "국가 산업을 적극 지원합니다.",
                "보조금 지급 (경제 +15, 종교 -5)", "지원 보류",
                "산업 활성화로 경제가 성장했지만 종교계 반발이 있었습니다.",
                "지원하지 않아 산업계가 아쉬워합니다.",
                15, 0, 0, -5, 0,
                0, 0, 0, 0, 0, false, "일반 이벤트"),

                // 군사 중심 이벤트
                Event("군비 증강", "국방 예산을 증액할 계획입니다.",
                      "증액 승인 (군사 +10, 경제 -5)", "보류",
                      "군사력이 증강되었지만 재정 부담이 커졌습니다.",
                      "군사 계획이 보류되었습니다.",
                      -5, 10, 0, 0, 0,
                      0, 0, 0, 0, 0, false, "일반 이벤트"),

                      // 민심 중심 이벤트
                      Event("공공 복지 확대", "복지 강화를 통해 국민의 삶의 질을 개선합니다.",
                            "복지 확대 (민심 +10, 경제 -5)", "보류",
                            "복지 확대에 국민이 만족했지만 예산 부담이 있습니다.",
                            "복지 확대가 무산되었습니다.",
                            -5, 0, 10, 0, 0,
                            0, 0, 0, 0, 0, false, "일반 이벤트"),

                            // 종교 중심 이벤트
                            Event("국가 기도일 지정", "국가적 차원의 기도일을 지정할 계획입니다.",
                                  "기도일 시행 (종교 +10, 군사 -5)", "무시",
                                  "신앙심이 고양되었지만 군사 훈련 일정에 차질이 있었습니다.",
                                  "기도일 지정이 무산되었습니다.",
                                  0, -5, 0, 10, 0,
                                  0, 0, 0, 0, 0, false, "일반 이벤트"),

                                  // 과학/마법 중심 이벤트
                                  Event("기술 연구소 설립", "최신 기술(또는 마법) 연구소를 설립합니다.",
                                        "설립 진행 (과학/마법 +10, 경제 -5)", "취소",
                                        "신기술/마법 발전이 이루어졌지만 재정 부담이 생겼습니다.",
                                        "연구소 설립 계획이 취소되었습니다.",
                                        -5, 0, 0, 0, 10,
                                         0, 0, 0, 0, 0, false, "일반 이벤트")
    };

    // ✅ 20% 확률로 업그레이드 이벤트
    if (allowUpgrade && rand() % 100 < 20) {
        return generateUpgradeEvent(player);
    }

    // ✅ 20% 확률로 연구 이벤트
    if (player.isMilitaryUpgraded() && !player.isResearchMaxed() && rand() % 100 < 20) {
        return generateResearchEvent(player);
    }

    // ✅ 20% 확률로 압박 이벤트 (자원 80 이상 중 하나라도 있을 경우)
    bool hasPressure =
        player.getEconomy() >= 80 || player.getMilitary() >= 80 ||
        player.getMorale() >= 80 || player.getReligion() >= 80 ||
        player.getScienceOrMagic() >= 80;

    if (hasPressure && rand() % 100 < 40) {
        return generatePressureEvent(player);
    }

    // ✅ 그 외 일반 이벤트
    int randomIndex = rand() % eventList.size();
    return eventList[randomIndex];
}




Event Event::generateBigEvent() {
    vector<Event> bigEvents = {
        Event("대규모 전쟁", "적국과의 대규모 전쟁이 시작되었습니다!",
              "전면전 수행 (군사 -20, 경제 +15)", "협상 시도 (군사 -10, 민심 +10)",
              "전면전을 수행하여 경제적 이득을 얻었지만, 많은 병력을 잃었습니다.",
              "협상을 시도하여 국민들이 안심했지만, 군사력이 줄어들었습니다.",
              15, -20, 0, 0, 0,  0, -10, 10, 0, 0, false, "빅 이벤트"),

        Event("왕국의 재정 위기", "국가 재정이 심각한 위기에 처했습니다.",
              "세금 대폭 인상 (경제 +20, 민심 -15)", "비상 대출 (경제 +10, 군사 -5)",
              "세금을 대폭 인상하여 경제를 살렸지만, 국민들의 불만이 커졌습니다.",
              "비상 대출을 받아 급한 불은 껐지만, 군사력이 약화되었습니다.",
              20, 0, -15, 0, 0,  10, -5, 0, 0, 0, false, "빅 이벤트")
    };

    int randomIndex = rand() % bigEvents.size();
    return bigEvents[randomIndex];
}

Event Event::generateUpgradeEvent(const Resources& player) {
    vector<Event> possibleUpgrades;

    // 조건 체크: 자원 60 이상 + 업그레이드 아직 안됨
    if (player.getMilitary() >= 60 && player.getEconomy() >= 60 && !player.hasMilitaryUpgrade()) {
        possibleUpgrades.push_back(Event(
            "군사 업그레이드 제안",
            "군사력과 경제력이 충분합니다. 군사 시스템을 업그레이드하시겠습니까?",
            "업그레이드 진행 (군사 업그레이드 완료)",
            "유지 (변화 없음)",
            "군사 업그레이드가 완료되었습니다.",
            "기존 시스템을 유지하기로 했습니다.",
            -20, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
            false,
            "업그레이드 이벤트"
        ));
    }

    if (player.getMorale() >= 60 && player.getEconomy() >= 60 && !player.hasMoraleUpgrade()) {
        possibleUpgrades.push_back(Event(
            "민심 업그레이드 제안",
            "민심과 경제가 안정적입니다. 민심 시스템을 업그레이드하시겠습니까?",
            "업그레이드 진행 (민심 업그레이드 완료)",
            "유지 (변화 없음)",
            "민심 업그레이드가 완료되었습니다.",
            "기존 민심 시스템을 유지하기로 했습니다.",
            -20, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
            false,
            "업그레이드 이벤트"
        ));
    }

    if (player.getReligion() >= 60 && player.getEconomy() >= 60 && !player.hasReligionUpgrade()) {
        possibleUpgrades.push_back(Event(
            "종교 업그레이드 제안",
            "종교와 경제가 안정적입니다. 종교 시스템을 업그레이드하시겠습니까?",
            "업그레이드 진행 (종교 업그레이드 완료)",
            "유지 (변화 없음)",
            "종교 업그레이드가 완료되었습니다.",
            "기존 종교 시스템을 유지하기로 했습니다.",
            -20, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
            false,
            "업그레이드 이벤트"
        ));
    }

    // ✅ 업그레이드 가능한 이벤트가 없으면 일반 이벤트 실행
    if (possibleUpgrades.empty()) {
        Event randomEvent = Event::generateRandomEvent(player);

        // ✅ 일반 이벤트가 다시 업그레이드 이벤트를 호출하지 않도록 보장
        while (randomEvent.getType() == "업그레이드 이벤트") {
            randomEvent = Event::generateRandomEvent(player);
        }

        return randomEvent;
    }

    // 무작위로 하나 선택
    return possibleUpgrades[rand() % possibleUpgrades.size()];
}

Event Event::generateRecoveryEvent(const Resources& player, int stage) {
    vector<Event> recoveryEvents;

    if (player.getEconomy() >= 100 && !player.hasRecoveryEventTriggered(0)) {
        if (stage == 1) {
            int roll = rand() % 100;
            bool success = roll < 60;
            int amount = roll % 20 + 31;
            int change = success ? -amount : 0;

            recoveryEvents.push_back(Event(
                "경제 회복 정책", "경제가 과열되었습니다. 인플레이션을 억제하시겠습니까?",
                "강제 조절 정책 시행 (확률적 경제 -31 이상)", "시장 자율에 맡긴다 (변화 없음)",
                success ? "인플레이션을 억제하여 경제가 안정되었습니다." : "정책이 실패하여 경제 과열 상태가 지속됩니다.",
                "시장에 맡겼으나, 경제는 여전히 과열된 상태입니다.",
                change, 0, 0, 0, 0, 0, 0, 0, 0, 0, true, "회생 이벤트"
            ));
        }
        else {
            recoveryEvents.push_back(Event(
                "경제 조정", "경제가 여전히 과열된 상태입니다. 추가 조정이 필요합니다.",
                "세율 인상 및 긴축 정책 시행 (경제 -15)", "변화 없음",
                "긴축 정책이 성공적으로 시행되었습니다.",
                "추가 조정을 하지 않아 경제 과열 상태가 유지됩니다.",
                -15, 0, 0, 0, 0, 0, 0, 0, 0, 0, true, "회생 이벤트"
            ));
        }
    }

    if (player.getMilitary() >= 100 && !player.hasRecoveryEventTriggered(1)) {
        if (stage == 1) {
            bool success = (rand() % 100 < 60);
            int change = success ? -(rand() % 20 + 31) : 0;
            recoveryEvents.push_back(Event(
                "군사 감축 논의", "군사력이 과도하게 증가하여 부담이 커지고 있습니다.",
                "군비 감축 단행 (확률적 군사 -31 이상)", "현재 상태 유지",
                success ? "군비를 감축하여 국방 예산을 절약했습니다." : "감축 시도가 실패하여 병력 유지비가 계속 부담됩니다.",
                "군사력을 그대로 유지하기로 결정했습니다.",
                0, change, 0, 0, 0, 0, 0, 0, 0, 0, true, "회생 이벤트"
            ));
        }
        else {
            recoveryEvents.push_back(Event(
                "군사 조정", "군사력이 여전히 과도한 상태입니다. 추가 조정이 필요합니다.",
                "국방 예산 축소 (군사 -15)", "변화 없음",
                "국방 예산 조정을 통해 균형을 맞췄습니다.",
                "추가 조정을 하지 않아 군사력이 그대로 유지됩니다.",
                0, -15, 0, 0, 0, 0, 0, 0, 0, 0, true, "회생 이벤트"
            ));
        }
    }

    if (player.getMorale() >= 100 && !player.hasRecoveryEventTriggered(2)) {
        if (stage == 1) {
            bool success = (rand() % 100 < 60);
            int change = success ? -(rand() % 20 + 31) : 0;
            recoveryEvents.push_back(Event(
                "사회 안정 대책", "과도한 민심으로 정부 운영에 어려움이 있습니다.",
                "강경 정책 도입 (확률적 민심 -31 이상)", "현재 상태 유지",
                success ? "사회가 안정되었으나 일부 반발이 있습니다." : "강경 정책이 실패하여 민심이 더욱 불안정해졌습니다.",
                "사회 혼란이 지속됩니다.",
                0, 0, change, 0, 0, 0, 0, 0, 0, 0, true, "회생 이벤트"
            ));
        }
        else {
            recoveryEvents.push_back(Event(
                "사회 안정 조치", "여전히 민심이 과도하게 높습니다.",
                "정부 개혁 진행 (민심 -15)", "변화 없음",
                "정부 개혁이 성공적으로 진행되었습니다.",
                "추가 조정을 하지 않아 민심이 계속 높습니다.",
                0, 0, -15, 0, 0, 0, 0, 0, 0, 0, true, "회생 이벤트"
            ));
        }
    }

    if (player.getReligion() >= 100 && !player.hasRecoveryEventTriggered(3)) {
        if (stage == 1) {
            bool success = (rand() % 100 < 60);
            int change = success ? -(rand() % 20 + 31) : 0;
            recoveryEvents.push_back(Event(
                "종교 개혁 논의", "종교적 영향력이 지나치게 확대되었습니다.",
                "종교적 개혁 단행 (확률적 종교 -31 이상)", "현재 상태 유지",
                success ? "종교 개혁을 통해 균형을 맞췄습니다." : "개혁이 실패하여 종교적 갈등이 심화되었습니다.",
                "종교적 영향력이 여전히 강합니다.",
                0, 0, 0, change, 0, 0, 0, 0, 0, 0, true, "회생 이벤트"
            ));
        }
        else {
            recoveryEvents.push_back(Event(
                "종교 조정", "여전히 종교적 영향력이 과도한 상태입니다.",
                "종교 활동 제한 (종교 -15)", "변화 없음",
                "종교적 영향력을 조정하여 균형을 맞췄습니다.",
                "추가 조정을 하지 않아 종교적 영향력이 지속됩니다.",
                0, 0, 0, -15, 0, 0, 0, 0, 0, 0, true, "회생 이벤트"
            ));
        }
    }

    if (player.getScienceOrMagic() >= 100 && !player.hasRecoveryEventTriggered(4)) {
        if (stage == 1) {
            bool success = (rand() % 100 < 60);
            int change = success ? -(rand() % 20 + 31) : 0;
            recoveryEvents.push_back(Event(
                (player.getNationType() == "Science") ? "과학 연구 조정" : "마법 균형 논의",
                "과학/마법이 지나치게 발전하여 불안 요소가 증가하고 있습니다.",
                (player.getNationType() == "Science") ? "연구 제한 조치 시행 (확률적 과학 -31 이상)" : "마법 억제 정책 시행 (확률적 마법 -31 이상)",
                "현재 상태 유지",
                success ? "연구/마법 균형을 맞추는 조치를 취했습니다." : "조정 시도가 실패하여 불균형이 지속됩니다.",
                "추가 조정을 하지 않아 불안 요소가 지속됩니다.",
                0, 0, 0, 0, change, 0, 0, 0, 0, 0, true, "회생 이벤트"
            ));
        }
        else {
            recoveryEvents.push_back(Event(
                (player.getNationType() == "Science") ? "과학 조정" : "마법 조정",
                "여전히 과학/마법이 과도하게 발전하고 있습니다.",
                (player.getNationType() == "Science") ? "연구 속도 조절 (과학 -15)" : "마법 사용 제한 (마법 -15)",
                "변화 없음",
                "조정이 성공적으로 이루어졌습니다.",
                "추가 조정을 하지 않아 불균형이 유지됩니다.",
                0, 0, 0, 0, -15, 0, 0, 0, 0, 0, true, "회생 이벤트"
            ));
        }
    }

    // ✅ 회생 이벤트가 없으면 일반 이벤트 반환 (무한 루프 방지)
    if (recoveryEvents.empty()) {
        Event randomEvent = Event::generateRandomEvent(player);
        while (randomEvent.getType() == "회생 이벤트") {
            randomEvent = Event::generateRandomEvent(player);
        }
        return randomEvent;
    }

    return recoveryEvents[rand() % recoveryEvents.size()];
}


string Event::getType() const {
    return type;
}

string Event::getTitle() const {
    return title;  //  이벤트 제목 반환
}

Event Event::generateNukeEvent(const Resources& player) {
    string title = (player.getNationType() == "Science") ? "핵폭탄 발사 결정" : "헬파이어 발사 의결";
    string description = (player.getNationType() == "Science")
        ? "모든 준비가 끝났습니다. 핵폭탄을 발사하시겠습니까?"
        : "모든 의식이 완성되었습니다. 헬파이어를 시전하시겠습니까?";

    string option1 = (player.getNationType() == "Science") ? "즉시 핵을 발사한다." : "지체 없이 헬파이어를 시전한다.";
    string option2 = (player.getNationType() == "Science") ? "고민 끝에 핵을 발사한다." : "망설이지만 결국 헬파이어를 시전한다.";

    string result1 = (player.getNationType() == "Science")
        ? "핵이 발사되었습니다. 적국은 순식간에 잿더미가 되었습니다."
        : "헬파이어가 시전되었습니다. 마법의 불꽃이 세상을 집어삼켰습니다.";

    string result2 = (player.getNationType() == "Science")
        ? "핵이 발사되었습니다. 과학의 힘이 세상을 지배합니다."
        : "헬파이어가 시전되었습니다. 마법의 힘이 절정을 이룹니다.";

    return Event(
        title,
        description,
        option1, option2,
        result1, result2,
        0, 0, 0, 0, 0,   // 선택 A 자원 변화 없음
        0, 0, 0, 0, 0,   // 선택 B 자원 변화 없음
        false,          // 회생 이벤트 아님
        "핵/헬파이어 이벤트"
    );
}

Event Event::generateResearchEvent(const Resources& player) {
    int level = player.getResearchLevel();
    int cost = 10 + level * 5;  // 연구 단계에 따라 경제 소모 증가

    string title = (player.getNationType() == "Science") ? "과학 연구 진행" : "마법 연구 진행";
    string description = (player.getNationType() == "Science")
        ? "과학 병기 개발을 위한 연구를 진행하시겠습니까?"
        : "헬파이어 시전을 위한 마법 연구를 수행하시겠습니까?";

    string option1 = (player.getNationType() == "Science")
        ? "과학 연구를 진행한다. (경제 -" + to_string(cost) + ")"
        : "마법 연구를 진행한다. (경제 -" + to_string(cost) + ")";

    string option2 = "아직 때가 아니다.";

    // ✅ 연구 단계별 메시지
    string result1;
    if (player.getNationType() == "Science") {
        switch (level) {
        case 0: result1 = "기초 이론 정립이 시작되었습니다."; break;
        case 1: result1 = "에너지 방출 패턴 분석이 완료되었습니다."; break;
        case 2: result1 = "정밀 핵융합 반응 설계가 진행 중입니다."; break;
        case 3: result1 = "발사체 설계가 최종 단계에 도달했습니다."; break;
        default: result1 = "과학 병기 연구가 완전히 완료되었습니다."; break;
        }
    }
    else {
        switch (level) {
        case 0: result1 = "기초 마법 진언이 수집되었습니다."; break;
        case 1: result1 = "마력 흐름의 증폭 구조를 파악했습니다."; break;
        case 2: result1 = "금기의 룬이 활성화되기 시작했습니다."; break;
        case 3: result1 = "헬파이어 시전 의식이 완성 직전입니다."; break;
        default: result1 = "마법 연구가 극에 달했습니다."; break;
        }
    }

    string result2 = "이번에는 연구를 진행하지 않았습니다.";

    return Event(
        title,
        description,
        option1,
        option2,
        result1,
        result2,
        -cost, 0, 0, 0, 0,   // 선택지 A: 경제 감소
        0, 0, 0, 0, 0,       // 선택지 B: 변화 없음
        false,
        "연구 이벤트"
    );
}

Event Event::generatePressureEvent(const Resources& player) {
    vector<Event> pressureEvents;

    if (player.getEconomy() >= 80) {
        pressureEvents.push_back(Event("경제에 대한 제재 압박", "상대국의 경제 자원이 과도하게 증가하고 있습니다. 압박을 가하겠습니까?",
            "경제 제재 실시 (내 -15, 상대 -10)", "그냥 둔다 (변화 없음)",
            "압박을 가해 상대의 경제 자원이 감소했습니다.", "압박을 가하지 않았습니다.",
            -15, 0, 0, 0, 0, 0, 0, 0, 0, 0, false, "압박 이벤트", PressureEffectType::DECREASE, 0));
        pressureEvents.push_back(Event("경제에 대한 획득 차단 압박", "상대국의 경제 자원이 과도하게 증가하고 있습니다. 압박을 가하겠습니까?",
            "경제 획득 차단 (상대 다음 턴 획득 불가)", "그냥 둔다 (변화 없음)",
            "상대의 경제 획득을 일시적으로 차단했습니다.", "압박을 가하지 않았습니다.",
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, false, "압박 이벤트", PressureEffectType::BLOCK, 0));
        pressureEvents.push_back(Event("경제에 대한 강제 지원 압박", "상대국의 경제 자원이 과도하게 증가하고 있습니다. 압박을 가하겠습니까?",
            "경제 지원 강행 (내 -10, 상대 +10)", "그냥 둔다 (변화 없음)",
            "상대에게 경제를 지원하여 외교적 압박을 가했습니다.", "압박을 가하지 않았습니다.",
            -10, 0, 0, 0, 0, 0, 0, 0, 0, 0, false, "압박 이벤트", PressureEffectType::SUPPORT, 0));
    }

    if (player.getMilitary() >= 80) {
        pressureEvents.push_back(Event("군사에 대한 제재 압박", "상대국의 군사 자원이 과도하게 증가하고 있습니다. 압박을 가하겠습니까?",
            "군사 제재 실시 (내 -15, 상대 -10)", "그냥 둔다 (변화 없음)",
            "압박을 가해 상대의 군사 자원이 감소했습니다.", "압박을 가하지 않았습니다.",
            0, -15, 0, 0, 0, 0, 0, 0, 0, 0, false, "압박 이벤트", PressureEffectType::DECREASE, 1));
        pressureEvents.push_back(Event("군사에 대한 획득 차단 압박", "상대국의 군사 자원이 과도하게 증가하고 있습니다. 압박을 가하겠습니까?",
            "군사 획득 차단 (상대 다음 턴 획득 불가)", "그냥 둔다 (변화 없음)",
            "상대의 군사 획득을 일시적으로 차단했습니다.", "압박을 가하지 않았습니다.",
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, false, "압박 이벤트", PressureEffectType::BLOCK, 1));
        pressureEvents.push_back(Event("군사에 대한 강제 지원 압박", "상대국의 군사 자원이 과도하게 증가하고 있습니다. 압박을 가하겠습니까?",
            "군사 지원 강행 (내 -10, 상대 +10)", "그냥 둔다 (변화 없음)",
            "상대에게 군사를 지원하여 외교적 압박을 가했습니다.", "압박을 가하지 않았습니다.",
            0, -10, 0, 0, 0, 0, 0, 0, 0, 0, false, "압박 이벤트", PressureEffectType::SUPPORT, 1));
    }

    if (player.getMorale() >= 80) {
        pressureEvents.push_back(Event("민심에 대한 제재 압박", "상대국의 민심 자원이 과도하게 증가하고 있습니다. 압박을 가하겠습니까?",
            "민심 제재 실시 (내 -15, 상대 -10)", "그냥 둔다 (변화 없음)",
            "압박을 가해 상대의 민심 자원이 감소했습니다.", "압박을 가하지 않았습니다.",
            0, 0, -15, 0, 0, 0, 0, 0, 0, 0, false, "압박 이벤트", PressureEffectType::DECREASE, 2));
        pressureEvents.push_back(Event("민심에 대한 획득 차단 압박", "상대국의 민심 자원이 과도하게 증가하고 있습니다. 압박을 가하겠습니까?",
            "민심 획득 차단 (상대 다음 턴 획득 불가)", "그냥 둔다 (변화 없음)",
            "상대의 민심 획득을 일시적으로 차단했습니다.", "압박을 가하지 않았습니다.",
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, false, "압박 이벤트", PressureEffectType::BLOCK, 2));
        pressureEvents.push_back(Event("민심에 대한 강제 지원 압박", "상대국의 민심 자원이 과도하게 증가하고 있습니다. 압박을 가하겠습니까?",
            "민심 지원 강행 (내 -10, 상대 +10)", "그냥 둔다 (변화 없음)",
            "상대에게 민심을 지원하여 외교적 압박을 가했습니다.", "압박을 가하지 않았습니다.",
            0, 0, -10, 0, 0, 0, 0, 0, 0, 0, false, "압박 이벤트", PressureEffectType::SUPPORT, 2));
    }

    if (player.getReligion() >= 80) {
        pressureEvents.push_back(Event("종교에 대한 제재 압박", "상대국의 종교 자원이 과도하게 증가하고 있습니다. 압박을 가하겠습니까?",
            "종교 제재 실시 (내 -15, 상대 -10)", "그냥 둔다 (변화 없음)",
            "압박을 가해 상대의 종교 자원이 감소했습니다.", "압박을 가하지 않았습니다.",
            0, 0, 0, -15, 0, 0, 0, 0, 0, 0, false, "압박 이벤트", PressureEffectType::DECREASE, 3));
        pressureEvents.push_back(Event("종교에 대한 획득 차단 압박", "상대국의 종교 자원이 과도하게 증가하고 있습니다. 압박을 가하겠습니까?",
            "종교 획득 차단 (상대 다음 턴 획득 불가)", "그냥 둔다 (변화 없음)",
            "상대의 종교 획득을 일시적으로 차단했습니다.", "압박을 가하지 않았습니다.",
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, false, "압박 이벤트", PressureEffectType::BLOCK, 3));
        pressureEvents.push_back(Event("종교에 대한 강제 지원 압박", "상대국의 종교 자원이 과도하게 증가하고 있습니다. 압박을 가하겠습니까?",
            "종교 지원 강행 (내 -10, 상대 +10)", "그냥 둔다 (변화 없음)",
            "상대에게 종교를 지원하여 외교적 압박을 가했습니다.", "압박을 가하지 않았습니다.",
            0, 0, 0, -10, 0, 0, 0, 0, 0, 0, false, "압박 이벤트", PressureEffectType::SUPPORT, 3));
    }

    if (player.getScienceOrMagic() >= 80) {
        pressureEvents.push_back(Event("과학/마법에 대한 제재 압박", "상대국의 과학/마법 자원이 과도하게 증가하고 있습니다. 압박을 가하겠습니까?",
            "과학/마법 제재 실시 (내 -15, 상대 -10)", "그냥 둔다 (변화 없음)",
            "압박을 가해 상대의 과학/마법 자원이 감소했습니다.", "압박을 가하지 않았습니다.",
            0, 0, 0, 0, -15, 0, 0, 0, 0, 0, false, "압박 이벤트", PressureEffectType::DECREASE, 4));
        pressureEvents.push_back(Event("과학/마법에 대한 획득 차단 압박", "상대국의 과학/마법 자원이 과도하게 증가하고 있습니다. 압박을 가하겠습니까?",
            "과학/마법 획득 차단 (상대 다음 턴 획득 불가)", "그냥 둔다 (변화 없음)",
            "상대의 과학/마법 획득을 일시적으로 차단했습니다.", "압박을 가하지 않았습니다.",
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, false, "압박 이벤트", PressureEffectType::BLOCK, 4));
        pressureEvents.push_back(Event("과학/마법에 대한 강제 지원 압박", "상대국의 과학/마법 자원이 과도하게 증가하고 있습니다. 압박을 가하겠습니까?",
            "과학/마법 지원 강행 (내 -10, 상대 +10)", "그냥 둔다 (변화 없음)",
            "상대에게 과학/마법을 지원하여 외교적 압박을 가했습니다.", "압박을 가하지 않았습니다.",
            0, 0, 0, 0, -10, 0, 0, 0, 0, 0, false, "압박 이벤트", PressureEffectType::SUPPORT, 4));
    }

    return pressureEvents[rand() % pressureEvents.size()];
}



Event Event::generateRingZoneEvent(const Resources& player) {
    vector<Event> ringEvents;

    // ✅ 내 이동 +2칸
    ringEvents.push_back(Event(
        "고대 지도의 발견",
        "고대 지도의 조각을 발견했습니다. 더 빠르게 절대 반지를 향해 나아갈 수 있습니다.",
        "지도를 따라간다 (+2칸 이동)", "무시하고 진행한다 (변화 없음)",
        "지도를 따라가며 길을 단축했습니다. 앞으로 +2칸 이동합니다.",
        "지도를 무시하고 원래 길을 따라갑니다.",
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        false,
        "반지 이벤트"
    ));

    // ✅ 상대 이동 방해
    ringEvents.push_back(Event(
        "마법 폭풍 소환",
        "주변 자연을 조작하여 적의 길을 방해할 수 있습니다.",
        "폭풍을 소환한다 (상대 이동 -1칸)", "그냥 둔다",
        "폭풍이 상대의 이동을 늦췄습니다.",
        "폭풍을 일으키지 않기로 했습니다.",
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        false,
        "반지 이벤트"
    ));

    return ringEvents[rand() % ringEvents.size()];
}

string Event::getDescription() const {
    return description;
}








