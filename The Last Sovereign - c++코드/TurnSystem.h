#pragma once

#include "Resources.h"

class TurnSystem {
private:
    Resources sciencePlayer; // 과학 왕국
    Resources magicPlayer;   // 마법 왕국
    Resources* currentPlayer; // 현재 턴 플레이어 (포인터 사용)

    int turn; // 현재 턴
    int researchCount = 0;  // ✅ 연구 횟수 (전체 게임에서 공유되는 값이면 필요)
    int ringPosition = 0;   // ✅ 절대반지 진행도
    int scienceResearchCount = 0;  // ✅ 과학 왕국 연구 횟수
    int magicResearchCount = 0;    // ✅ 마법 왕국 연구 횟수

public:
    TurnSystem(); // 생성자
    void start(); // 게임 시작
    void playTurn(); // 턴 진행
    void swapCurrentPlayer(); // ✅ 플레이어 교체 기능 추가
    bool checkEnd(); // 게임 종료 조건 확인
};


