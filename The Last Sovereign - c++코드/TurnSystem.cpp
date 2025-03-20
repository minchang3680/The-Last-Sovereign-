#include "TurnSystem.h"
#include "Event.h"
#include <iostream>
#include <tuple>

using namespace std;

// 🔹 생성자: turn을 1부터 시작
TurnSystem::TurnSystem()
    : sciencePlayer("Science"), magicPlayer("Magic"), turn(1) {
    currentPlayer = &sciencePlayer; // 과학 왕국이 먼저 시작
}

void TurnSystem::start() {
    cout << "게임을 시작합니다." << endl;

    while (!checkEnd()) {
        // ✅ Science 플레이어 턴 실행
        currentPlayer = &sciencePlayer;
        playTurn();

        // ✅ Magic 플레이어 턴 실행
        currentPlayer = &magicPlayer;
        playTurn();

        // ✅ 두 플레이어가 턴을 마친 후에만 턴 증가
        turn++;
    }
}

void TurnSystem::playTurn() {
    // ✅ 각 왕국의 턴에도 턴 번호 표시
    cout << "===== 턴 " << turn << " =====\n" << endl;

    // ✅ 현재 플레이어 출력
    cout << "[ " << currentPlayer->getNationType() << " 왕국의 턴 ]\n" << endl;

    // ✅ 현재 자원 상태 출력
    currentPlayer->display();
    cout << endl;

    // ✅ 랜덤 이벤트 발생
    Event randomEvent = Event::generateRandomEvent();
    randomEvent.displayEvent(currentPlayer->getNationType());  // ✅ 국가 유형 전달!
    randomEvent.applyEvent(*currentPlayer);

    // ✅ 결과 가독성을 위한 줄바꿈 추가
    cout << "\n----------------------------\n" << endl;

    // ✅ 100% 초과된 자원 확인 (턴 유지 카운트)
    currentPlayer->trackMaxResourceTurns();

    // ✅ 게임 오버 확인
    if (currentPlayer->checkGameOver()) {
        cout << "패배 조건 충족! 게임이 종료됩니다." << endl;
        exit(0);
    }
}



bool TurnSystem::checkEnd() {
    // ✅ 1. 플레이어가 패배했는지 확인
    if (sciencePlayer.checkGameOver() || magicPlayer.checkGameOver()) {
        return true;  // 패배 조건 충족 → 게임 종료
    }

    // ✅ 2. 연구 승리 조건 확인
    if (scienceResearchCount >= 4 && sciencePlayer.getMilitary() >= 60) {
        cout << "\n승리! 과학 왕국이 핵폭탄을 개발하여 전쟁에서 승리했습니다!" << endl;
        return true;
    }
    if (magicResearchCount >= 4 && magicPlayer.getMilitary() >= 60) {
        cout << "\n승리! 마법 왕국이 헬파이어 마법을 완성하여 세계를 지배했습니다!" << endl;
        return true;
    }

    // ✅ 3. 절대반지 승리 조건 확인 (50턴 이후)
    if (turn >= 50) {
        int roll = (rand() % 3) + 1;  // 1~3칸 이동
        ringPosition += roll;

        cout << "절대 반지를 향해 이동: " << roll << "칸 (현재 위치: " << ringPosition << ")\n";

        if (ringPosition >= 75) {
            cout << "\n절대 반지를 획득했습니다! 즉시 승리!\n";
            return true;
        }
    }

    return false; // 게임 계속 진행
}







