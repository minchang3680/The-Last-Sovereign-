// DefeatCondition.h
#pragma once
#include "Resources.h"

class DefeatCondition {
public:
    // 자원 중 하나라도 0 이하일 경우
    static bool checkResourceZero(const Resources& player);

    // 자원이 100% 이상 상태로 2턴 이상 유지되었을 경우
    static bool checkResourceOverflowFail(const Resources& player);

    // 상대가 절대반지 획득했을 경우
    static bool checkDefeatByRing(int ringPosition);

    // 각 패배 조건에 따른 메시지 출력 및 게임 종료
    static void declareResourceZeroDefeat(const Resources& loser, const Resources& winner);
    static void declareOverflowDefeat(const Resources& loser, const Resources& winner);
    static void declareRingDefeat(const Resources& loser, const Resources& winner);
    static void declareNukeDefeat(const Resources& loser, const Resources& winner);
    // 자원 중 100 이상인 자원의 인덱스를 반환 (0~4), 없으면 -1
    static int getOverflowTarget(const Resources& player);
    static int getImmediateOverflowTarget(const Resources& player);
};

