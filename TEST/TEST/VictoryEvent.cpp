// VictoryEvent.cpp
#include "VictoryEvent.h"


void VictoryEvent::executeNuclearVictory(const Resources& winner, const Resources& loser) {
    if (winner.getNationType() == "Science") {
        cout << "\n 과학 왕국이 핵폭탄을 발사하였습니다! 마법 왕국이 전멸하였습니다.\n";
    }
    else {
        cout << "\n 마법 왕국이 헬파이어를 시전하였습니다! 과학 왕국이 소멸하였습니다.\n";
    }
    cout << winner.getNationType() << " 왕국의 승리!\n";
    exit(0);
}

void VictoryEvent::executeRingVictory(const Resources& winner, const Resources& loser) {
    cout << "\n " << winner.getNationType() << " 왕국이 절대 반지를 획득하였습니다!" << endl;
    cout << loser.getNationType() << " 왕국은 절대 복종할 수밖에 없었습니다." << endl;
    cout << winner.getNationType() << " 왕국의 승리!\n";
    exit(0);
}
