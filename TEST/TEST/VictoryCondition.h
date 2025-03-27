// VictoryCondition.h
#pragma once
#include "Resources.h"  // �ʿ� ��

class VictoryCondition {
public:
    // ����ź / �����̾� ���� �޼� ���� �Ǵ�
    static bool checkVictoryByNuke(const Resources& player);

    // ��/�����̾�� �¸�
    static void declareNukeVictory(const Resources& winner, const Resources& loser);

    // ��������� �¸�
    static void declareRingVictory(const Resources& winner, const Resources& loser);

    // ��� �й�� ���� �Ϲ� �¸�
    static void declareStandardVictory(const Resources& winner, const Resources& loser);

    // ������� �¸� ���� (75ĭ ����)
    static bool checkVictoryByRing(int ringPosition);

    // �Ϲ� �¸�: ��밡 �й� ������ �����ߴ��� Ȯ��
    static bool checkVictoryByDefeatOfOpponent(const Resources& opponent);

    static bool canTriggerNukeEvent(const Resources& player);
};
