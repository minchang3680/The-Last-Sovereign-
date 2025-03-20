#include "TurnSystem.h"
#include "Event.h"
#include <iostream>
#include <tuple>
#include <thread>  // sleep_for 사용
#include <chrono>  // 시간 관련 기능

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
    cout << "\n\n===== 턴 " << turn << " =====\n" << endl;
    cout << "[ " << currentPlayer->getNationType() << " 왕국의 턴 ]\n" << endl;
    currentPlayer->display();
    cout << endl;

    // ✅ 4턴마다 경제 보급
    if (turn % 4 == 0) {
        cout << "📢 경제 보급! 국가에서 경제 지원을 받습니다. (경제 +10)\n";
        currentPlayer->modify(10, 0, 0, 0, 0);
    }

    // ✅ 랜덤 이벤트 생성 및 표시
    Event randomEvent = Event::generateRandomEvent();
    randomEvent.displayEvent();

    // ✅ 플레이어 선택 받기
    char choice;
    do {
        cout << "\n🔹 선택 (1 또는 2): ";
        cin >> choice;
    } while (choice != '1' && choice != '2');

    // ✅ 선택 적용
    randomEvent.applyEvent(*currentPlayer, choice);

    // ✅ 100% 초과된 자원 확인 (턴 유지 카운트)
    currentPlayer->trackMaxResourceTurns();

    // ✅ 게임 오버 확인
    if (currentPlayer->checkGameOver(*getOpponentPlayer())) {
        exit(0);
    }

    // ✅ 선택 후 1.5초 동안 딜레이 추가
    this_thread::sleep_for(chrono::milliseconds(500));  // 0.5초 대기
}





bool TurnSystem::checkEnd() {
    // ✅ 1. 패배 조건 확인
    if (sciencePlayer.checkGameOver(magicPlayer) || magicPlayer.checkGameOver(sciencePlayer)) {
        return true;
    }

    // ✅ 2. 헬파이어/핵폭탄 즉시 승리
    if (scienceResearchCount >= 4 && sciencePlayer.getMilitary() >= 60) {
        cout << "\n과학 왕국이 핵폭탄을 개발하여 전쟁에서 승리했습니다!" << endl;
        exit(0);
    }
    if (magicResearchCount >= 4 && magicPlayer.getMilitary() >= 60) {
        cout << "\n마법 왕국이 헬파이어 마법을 완성하여 세계를 지배했습니다!" << endl;
        exit(0);
    }

    // ✅ 3. 절대반지 승리 조건 확인 (50턴 이후 & 위치 75 도달)
    if (turn >= 50) {
        int roll = (rand() % 3) + 1;  // 1~3칸 이동
        ringPosition += roll;

        cout << "절대 반지를 향해 이동: " << roll << "칸 (현재 위치: " << ringPosition << ")\n";

        if (ringPosition >= 75) {
            if (currentPlayer->getNationType() == "Science") {
                cout << "\n과학 왕국이 절대반지를 획득했습니다! 즉시 승리!\n";
            }
            else {
                cout << "\n마법 왕국이 절대반지를 획득했습니다! 즉시 승리!\n";
            }
            exit(0);  // ✅ 즉시 종료 추가
        }
    }

    return false;
}








