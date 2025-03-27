// DefeatCondition.h
#pragma once
#include "Resources.h"

class DefeatCondition {
public:
    // �ڿ� �� �ϳ��� 0 ������ ���
    static bool checkResourceZero(const Resources& player);

    // �ڿ��� 100% �̻� ���·� 2�� �̻� �����Ǿ��� ���
    static bool checkResourceOverflowFail(const Resources& player);

    // ��밡 ������� ȹ������ ���
    static bool checkDefeatByRing(int ringPosition);

    // �� �й� ���ǿ� ���� �޽��� ��� �� ���� ����
    static void declareResourceZeroDefeat(const Resources& loser, const Resources& winner);
    static void declareOverflowDefeat(const Resources& loser, const Resources& winner);
    static void declareRingDefeat(const Resources& loser, const Resources& winner);
    static void declareNukeDefeat(const Resources& loser, const Resources& winner);
    // �ڿ� �� 100 �̻��� �ڿ��� �ε����� ��ȯ (0~4), ������ -1
    static int getOverflowTarget(const Resources& player);
    static int getImmediateOverflowTarget(const Resources& player);
};

