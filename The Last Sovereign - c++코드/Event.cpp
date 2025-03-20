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
void Event::displayEvent(const string& nationType) const {
    cout << "\n[이벤트 발생] " << name << endl;
    cout << description << endl;

    // 🔹 변화량을 저장할 벡터
    vector<string> changes;

    if (static_cast<int>(economyChange) != 0)
        changes.push_back("경제 " + string((economyChange > 0 ? "+" : "")) + to_string(static_cast<int>(economyChange)));
    if (static_cast<int>(militaryChange) != 0)
        changes.push_back("군사 " + string((militaryChange > 0 ? "+" : "")) + to_string(static_cast<int>(militaryChange)));
    if (static_cast<int>(moraleChange) != 0)
        changes.push_back("민심 " + string((moraleChange > 0 ? "+" : "")) + to_string(static_cast<int>(moraleChange)));
    if (static_cast<int>(religionChange) != 0)
        changes.push_back("종교 " + string((religionChange > 0 ? "+" : "")) + to_string(static_cast<int>(religionChange)));

    // 🔹 과학/마법 변경값을 국가 유형에 따라 다르게 출력
    if (static_cast<int>(scienceOrMagicChange) != 0) {
        if (nationType == "Science") {
            changes.push_back("과학 " + string((scienceOrMagicChange > 0 ? "+" : "")) + to_string(static_cast<int>(scienceOrMagicChange)));
        }
        else if (nationType == "Magic") {
            changes.push_back("마법 " + string((scienceOrMagicChange > 0 ? "+" : "")) + to_string(static_cast<int>(scienceOrMagicChange)));
        }
    }

    // 🔹 변경 사항 출력 (0인 값은 출력 안 함)
    for (size_t i = 0; i < changes.size(); i++) {
        cout << changes[i];
        if (i < changes.size() - 1) cout << ", ";
    }
    cout << endl;
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
