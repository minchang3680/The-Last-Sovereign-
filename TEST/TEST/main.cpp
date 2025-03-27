// main.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono> // ✅ 헤더는 파일 상단에만

#include "TurnSystem.h"

Resources player1("Science");
Resources player2("Magic");

int main() {
    // ✅ 밀리초 단위로 시드 설정
    unsigned int seed = static_cast<unsigned int>(
        std::chrono::system_clock::now().time_since_epoch().count()
        );
    srand(seed);
    std::cout << "[DEBUG] 시드: " << seed << std::endl;

    // ✅ rand() 몇 번 태워서 시퀀스 흐트러뜨리기
    int skip = rand() % 10 + 1;
    for (int i = 0; i < skip; i++) {
        volatile int dummy = rand();
    }

    std::cout << "===========================" << std::endl;
    std::cout << "    The Last Sovereign " << std::endl;
    std::cout << "===========================\n" << std::endl;

    //TurnSystem game;
    TurnSystem system;
    system.debugSkipToRingTest = true;
    //game.start();
    system.start();

    return 0;
}

