#pragma once
#include <string>
#include <vector>

class Resources {
private:
    std::string nationType;

    int economy;
    int military;
    int morale;
    int religion;
    int scienceOrMagic;

    int maxEconomy;
    int maxMilitary;
    int maxMorale;
    int maxReligion;
    int maxScienceOrMagic;

    bool nukeLaunched;

    std::vector<int> turnAtMax;

    bool militaryUpgraded;
    bool religionUpgraded;
    bool moraleUpgraded;
    int researchLevel;

    bool recoveryEventTriggered[5];
    bool resourceBlocked[5];  // 차단 여부

public:
    Resources();
    Resources(std::string nation);  // 생성자

    void modify(int eco, int mil, int mor, int rel, int sci, bool suppressOutput = false);
    void display();

    void trackMaxResourceTurns();

    std::string getNationType() const;

    int getEconomy() const;
    int getMilitary() const;
    int getMorale() const;
    int getReligion() const;
    int getScienceOrMagic() const;

    bool isMilitaryUpgraded() const;
    bool isReligionUpgraded() const;
    bool isMoraleUpgraded() const;

    void upgradeMilitary();
    void upgradeReligion();
    void upgradeMorale();

    bool hasMilitaryUpgrade() const;
    bool hasReligionUpgrade() const;
    bool hasMoraleUpgrade() const;

    void launchNuke();
    bool hasLaunchedNuke() const;

    int getResearchLevel() const;
    void increaseResearchLevel();
    bool isResearchMaxed() const;

    std::vector<int>& getTurnAtMax();
    const std::vector<int>& getTurnAtMax() const;

    bool hasRecoveryEventTriggered(int index) const;
    void setRecoveryEventTriggered(int index);

    int getMaxEconomy() const;
    int getMaxMilitary() const;
    int getMaxMorale() const;
    int getMaxReligion() const;
    int getMaxScienceOrMagic() const;

    void blockResource(int index);
    bool isResourceBlocked(int index) const;
    void clearAllBlocks();
};
