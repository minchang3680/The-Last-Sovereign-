#include <iostream>
#include "TurnSystem.h"

using namespace std;

int main() {
    cout << "=== The Last Sovereign ===" << endl;
    cout << "게임을 시작합니다...\n" << endl;

    srand(time(0)); // ✅ 난수 시드 설정 (한 번만 실행)

    TurnSystem game;
    game.start();

    return 0;
}


