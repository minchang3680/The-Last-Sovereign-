// 자원관리

#pragma once
#include <iostream>
#include <string>
using namespace std;

// 자원 클래스
class Resources {
private:
	int economy; //경제
	int military; //군사
	int morale; //민심
	int religion; //종교
	int scienceOrMagic; //과학 혹은 마법

	string nationType; // "Science" 또는 "Magic" (국가 타입)

	int maxEconomy; // 경제 최대치
	int maxMilitary; // 군사 최대치
	int maxMorale; // 민심 최대치
	int maxReligion; // 종교 최대치
	int maxScienOrMagic; // 과학 혹은 마법 최대치

	int turnAtMax[5]; // 100% 초과 상태가 유지된 턴 수 
	// -> 1.경제 2. 군사 3. 민심 4. 종교 5. 과학/마법으로 총 5개이므로 [5]이다.

public:
	string getNationType() const;
	int getMilitary() const; // ✅ 군사력 값을 반환하는 함수 추가
	Resources();
	Resources(string nation);
	void modify(int eco, int mil,int mor, int rel, int sciMag);	// 자원 변경
	bool checkGameOver(Resources& opponent); // 게임오버확인
	void trackMaxResourceTurns(); // 자원100%이상 유지 확인
	void display(); //현재 각 자원 상태 확인
};