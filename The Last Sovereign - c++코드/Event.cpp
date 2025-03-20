#include "Event.h"
#include <iostream>
#include <vector>
#include <cstdlib>  // 랜덤 값 생성
#include <ctime>

using namespace std;

// 🔹 생성자: 이벤트의 기본 정보 설정
Event::Event(string n, string desc, int eco, int mil, int mor, int rel, int sciMag)
    : name(n), description(desc), economyChange(eco), militaryChange(mil),
    moraleChange(mor), religionChange(rel), scienceOrMagicChange(sciMag) {
}

// 🔹 이벤트 내용 출력
void Event::displayEvent() const {
    cout << "\n📜 이벤트 발생: " << name << endl;
    cout << description << endl;
    cout << "변화: 경제(" << economyChange << "), 군사(" << militaryChange
        << "), 민심(" << moraleChange << "), 종교(" << religionChange
        << "), 과학/마법(" << scienceOrMagicChange << ")\n";
}

// 🔹 이벤트를 플레이어에게 적용
void Event::applyEvent(Resources& player) {
    player.modify(economyChange, militaryChange, moraleChange, religionChange, scienceOrMagicChange);
}

// 🔹 랜덤 이벤트 생성 (확률 기반)
Event Event::generateRandomEvent() {

    vector<Event> eventList = {
        Event("풍년!", "경제가 활기를 띠었습니다.", 10, 0, 5, 0, 0),
        Event("전쟁의 기운", "군사력이 증가했습니다.", 0, 10, -5, 0, 0),
        Event("종교적 개혁", "종교적 신념이 강화되었습니다.", 0, 0, 0, 10, -5),
        Event("과학 발전", "과학 기술이 크게 발전했습니다.", 0, 0, 0, 0, 15),
        Event("마법의 대격변", "마법이 폭발적으로 성장했습니다.", 0, 0, 0, 0, 15),
        Event("세금 감면", "경제적 지원이 증가했습니다.", 15, 0, -5, 0, 0),
        Event("민심 동요", "민심이 흔들렸습니다.", 0, 0, -10, 0, 0),
        Event("성직자의 가르침", "종교가 강화되었습니다.", 0, 0, 0, 10, 0)
    };

    int randomIndex = rand() % eventList.size();
    return eventList[randomIndex];
}
