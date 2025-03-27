#include "TurnSystem.h"
#include "Resources.h"
#include "Event.h"
#include "VictoryCondition.h"
#include "DefeatCondition.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;

TurnSystem::TurnSystem()
    : player1("Science"),
    player2("Magic"),
    currentPlayer(&player1),
    turn(1),
    ringPosition1(0),
    ringPosition2(0),
    scienceResearchCount(0),
    magicResearchCount(0)
{
}

void TurnSystem::start() {
    cout << "=== The Last Sovereign ===" << endl;
    cout << "게임을 시작합니다...\n" << endl;

    if (debugSkipToRingTest) {
        turn = 1;
        cout << "[디버그] 절대반지 테스트를 위해 50턴부터 시작합니다.\n";
    }
    else {
        turn = 1;
    }

    while (!checkEnd()) {
        currentPlayer = &player1;
        playTurn();

        currentPlayer = &player2;
        playTurn();

        turn++;
    }
}

void TurnSystem::playTurn() {
    cout << "\n===" << turn << "턴===" << endl;
    cout << currentPlayer->getNationType() << " 왕국의 턴\n" << endl;

    if (currentPlayer->hasReligionUpgrade()) {
        Resources& opponent = getOpponent(*currentPlayer);
        vector<string> resourceNames = { "경제", "군사", "민심", "종교", currentPlayer->getNationType() == "Science" ? "과학" : "마법" };
        vector<int> values = {
            opponent.getEconomy(),
            opponent.getMilitary(),
            opponent.getMorale(),
            opponent.getReligion(),
            opponent.getScienceOrMagic()
        };
        vector<int> indices = { 0, 1, 2, 3, 4 };
        random_shuffle(indices.begin(), indices.end());

        cout << "\n 종교 업그레이드 효과! 상대 자원 중 일부가 감지되었습니다." << endl;
        for (int i = 0; i < 2; ++i) {
            int idx = indices[i];
            cout << "- " << resourceNames[idx] << ": " << values[idx] << endl;
        }
    }

    int& ringPosition = (currentPlayer == &player1) ? ringPosition1 : ringPosition2;
    int& opponentRingPosition = (currentPlayer == &player1) ? ringPosition2 : ringPosition1;

    if (turn % 4 == 0) {
        int supply = currentPlayer->hasMoraleUpgrade() ? 10 : 5;
        currentPlayer->modify(supply, 0, 0, 0, 0, true);
        cout << "세금 징수하여 경제가 증가하였습니다. (경제 +" << supply << ")\n" << endl;
    }

    currentPlayer->display();

    if (VictoryCondition::checkVictoryByNuke(*currentPlayer)) {
        VictoryCondition::declareNukeVictory(*currentPlayer, *getOpponentPlayer());
    }

    if (VictoryCondition::canTriggerNukeEvent(*currentPlayer)) {
        Event nukeEvent = Event::generateNukeEvent(*currentPlayer);
        nukeEvent.displayEvent();

        char choice;
        do {
            cout << "선택 (1 또는 2): ";
            cin >> choice;
        } while (choice != '1' && choice != '2');

        nukeEvent.applyEvent(*currentPlayer, choice, ringPosition, opponentRingPosition);

        if (currentPlayer->hasLaunchedNuke()) {
            VictoryCondition::declareNukeVictory(*currentPlayer, *getOpponentPlayer());
        }
        return;
    }

    if (turn % 6 == 0) {
        Event bigEvent = Event::generateBigEvent();
        bigEvent.displayEvent();

        char choice;
        do {
            cout << "\n 선택 (1 또는 2): ";
            cin >> choice;
        } while (choice != '1' && choice != '2');

        bigEvent.applyEvent(*currentPlayer, choice, ringPosition, opponentRingPosition);
    }
    else {
        int targetIndex = DefeatCondition::getImmediateOverflowTarget(*currentPlayer);
        if (targetIndex != -1 && !currentPlayer->hasRecoveryEventTriggered(targetIndex)) {
            currentPlayer->setRecoveryEventTriggered(targetIndex);
            currentPlayer->trackMaxResourceTurns();
            int stage = currentPlayer->getTurnAtMax()[targetIndex] <= 1 ? 1 : 2;
            Event recoveryEvent = Event::generateRecoveryEvent(*currentPlayer, stage);
            recoveryEvent.displayEvent();

            char choice;
            do {
                cout << "\n 선택 (1 또는 2): ";
                cin >> choice;
            } while (choice != '1' && choice != '2');

            recoveryEvent.applyEvent(*currentPlayer, choice, ringPosition, opponentRingPosition);
        }
        else {
            Event event = Event::generateRandomEvent(*currentPlayer);
            event.displayEvent();

            char choice;
            do {
                cout << "\n 선택 (1 또는 2): ";
                cin >> choice;
            } while (choice != '1' && choice != '2');

            event.applyEvent(*currentPlayer, choice, ringPosition, opponentRingPosition);
            currentPlayer->trackMaxResourceTurns();

            int postIndex = DefeatCondition::getImmediateOverflowTarget(*currentPlayer);
            if (postIndex != -1 && !currentPlayer->hasRecoveryEventTriggered(postIndex)) {
                currentPlayer->setRecoveryEventTriggered(postIndex);
                int stage = currentPlayer->getTurnAtMax()[postIndex] == 1 ? 1 : 2;
                Event recoveryEvent = Event::generateRecoveryEvent(*currentPlayer, stage);
                recoveryEvent.displayEvent();

                char recChoice;
                do {
                    cout << "\n 선택 (1 또는 2): ";
                    cin >> recChoice;
                } while (recChoice != '1' && recChoice != '2');

                recoveryEvent.applyEvent(*currentPlayer, recChoice, ringPosition, opponentRingPosition);
                currentPlayer->setRecoveryEventTriggered(postIndex);
            }
        }
    }

    if (turn >= 50) {
        int move = rand() % 3 + 1;
        ringPosition += move;
        cout << "절대반지를 향해 " << move << "칸 이동합니다. (현재 위치: " << ringPosition << ")\n";

        if (ringPosition >= 55 && rand() % 100 < 30) {
            Event ringEvent = Event::generateRingZoneEvent(*currentPlayer);
            ringEvent.displayEvent();

            char choice;
            do {
                cout << "\n 선택 (1 또는 2): ";
                cin >> choice;
            } while (choice != '1' && choice != '2');

            ringEvent.applyEvent(*currentPlayer, choice, ringPosition, opponentRingPosition);
        }

        if (VictoryCondition::checkVictoryByRing(ringPosition)) {
            VictoryCondition::declareRingVictory(*currentPlayer, *getOpponentPlayer());
        }
    }

    if (DefeatCondition::checkResourceZero(*currentPlayer)) {
        DefeatCondition::declareResourceZeroDefeat(*currentPlayer, *getOpponentPlayer());
    }
    if (DefeatCondition::checkResourceOverflowFail(*currentPlayer)) {
        DefeatCondition::declareOverflowDefeat(*currentPlayer, *getOpponentPlayer());
    }
    if (DefeatCondition::checkDefeatByRing(opponentRingPosition)) {
        DefeatCondition::declareRingDefeat(*currentPlayer, *getOpponentPlayer());
    }

    this_thread::sleep_for(chrono::milliseconds(500));
}

void TurnSystem::swapCurrentPlayer() {
    currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
}

bool TurnSystem::checkEnd() {
    return false;
}

Resources* TurnSystem::getOpponentPlayer() {
    return (currentPlayer == &player1) ? &player2 : &player1;
}

Resources& TurnSystem::getOpponent(Resources& player) {
    return (&player == &player1) ? player2 : player1;
}

int TurnSystem::getCurrentTurn() const {
    return currentTurn;
}
