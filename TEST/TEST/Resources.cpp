#include "Resources.h"
#include <iostream>
using namespace std;

Resources::Resources() : Resources("Science") {}

Resources::Resources(string nation)
    : nationType(nation), economy(50), military(50), morale(50),
    religion(50), scienceOrMagic(50), maxEconomy(100), maxMilitary(100),
    maxMorale(100), maxReligion(100), maxScienceOrMagic(100),
    nukeLaunched(false), militaryUpgraded(false), religionUpgraded(false),
    moraleUpgraded(false), researchLevel(0) {
    turnAtMax = std::vector<int>(5, 0);
    for (int i = 0; i < 5; ++i) {
        recoveryEventTriggered[i] = false;
        resourceBlocked[i] = false;
    }
}

void Resources::modify(int eco, int mil, int mor, int rel, int sci, bool suppressOutput) {
    if (!resourceBlocked[0]) economy += eco;
    if (!resourceBlocked[1]) military += mil;
    if (!resourceBlocked[2]) morale += mor;
    if (!resourceBlocked[3]) religion += rel;
    if (!resourceBlocked[4]) scienceOrMagic += sci;
}

void Resources::display() {
    cout << "경제: " << economy << " / 군사: " << military
        << " / 민심: " << morale << " / 종교: " << religion
        << " / 과학/마법: " << scienceOrMagic << endl;
}

void Resources::trackMaxResourceTurns() {
    int values[5] = { economy, military, morale, religion, scienceOrMagic };
    int maxValues[5] = { maxEconomy, maxMilitary, maxMorale, maxReligion, maxScienceOrMagic };

    for (int i = 0; i < 5; ++i) {
        if (values[i] >= maxValues[i]) {
            turnAtMax[i]++;
        }
        else {
            turnAtMax[i] = 0;
        }
    }
}

string Resources::getNationType() const { return nationType; }

int Resources::getEconomy() const { return economy; }
int Resources::getMilitary() const { return military; }
int Resources::getMorale() const { return morale; }
int Resources::getReligion() const { return religion; }
int Resources::getScienceOrMagic() const { return scienceOrMagic; }

bool Resources::isMilitaryUpgraded() const { return militaryUpgraded; }
bool Resources::isReligionUpgraded() const { return religionUpgraded; }
bool Resources::isMoraleUpgraded() const { return moraleUpgraded; }

void Resources::upgradeMilitary() { militaryUpgraded = true; }
void Resources::upgradeReligion() { religionUpgraded = true; }
void Resources::upgradeMorale() { moraleUpgraded = true; }

bool Resources::hasMilitaryUpgrade() const { return militaryUpgraded; }
bool Resources::hasReligionUpgrade() const { return religionUpgraded; }
bool Resources::hasMoraleUpgrade() const { return moraleUpgraded; }

void Resources::launchNuke() { nukeLaunched = true; }
bool Resources::hasLaunchedNuke() const { return nukeLaunched; }

int Resources::getResearchLevel() const { return researchLevel; }
void Resources::increaseResearchLevel() {
    if (researchLevel < 4) researchLevel++;
}
bool Resources::isResearchMaxed() const {
    return researchLevel >= 4;
}

vector<int>& Resources::getTurnAtMax() { return turnAtMax; }
const vector<int>& Resources::getTurnAtMax() const { return turnAtMax; }

bool Resources::hasRecoveryEventTriggered(int index) const {
    return recoveryEventTriggered[index];
}
void Resources::setRecoveryEventTriggered(int index) {
    recoveryEventTriggered[index] = true;
}

int Resources::getMaxEconomy() const { return maxEconomy; }
int Resources::getMaxMilitary() const { return maxMilitary; }
int Resources::getMaxMorale() const { return maxMorale; }
int Resources::getMaxReligion() const { return maxReligion; }
int Resources::getMaxScienceOrMagic() const { return maxScienceOrMagic; }

void Resources::blockResource(int index) { resourceBlocked[index] = true; }
bool Resources::isResourceBlocked(int index) const { return resourceBlocked[index]; }
void Resources::clearAllBlocks() {
    for (int i = 0; i < 5; ++i) resourceBlocked[i] = false;
}
