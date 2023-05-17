#include "SmartTeam.hpp"
#include <cfloat>
namespace ariel {

    bool is_healthy(Character* ninja) {
        if(ninja->getHitPoints() > 40){
            return true ;
        }
        return false ;
    }

    bool can_shoot(Character* enemy) {
        if(enemy->getHitPoints() > 40){
            return true ;
        }
        return false ;
    }


///----- Given a character and a team, this method returns the team`s character that is closest to the source character     -----
///----- (Without including the character himself). this method being used on findNewLeader function and on attack function -----
    Character *findMinDist(Character *source, SmartTeam &team) {
        Character *currentCandidate = NULL;
        double min_dist = DBL_MAX;
        double current_dist = 0;

        //----- Iterate over the team characters and get the character with min distance from the given source -----
        for (Character *character: team.characters) {
            if (character != source) {
                if (character->isAlive()) {
                    current_dist = character->distance(character);
                    if (current_dist < min_dist) {
                        min_dist = current_dist;
                        currentCandidate = character;
                    }
                }
            }
        }

        //----- Return the closest character -----
        return currentCandidate;
    }

    Character* SmartTeam::getCowboysTarget(SmartTeam *targetTeam){
        Character* closest = NULL ;
        double cumulativeDistance = 0, avgDist, minAvgDist = DBL_MAX ;
        int numOfPlayers = 0 ;
        for(Character* enemy: targetTeam->characters){
            if(enemy->isAlive()) {
                for (Character *teamPlayer: characters) {
                    if(teamPlayer->isAlive()){
                        cumulativeDistance += teamPlayer->distance(enemy) ;
                        numOfPlayers++ ;
                    }
                }
                avgDist = cumulativeDistance/numOfPlayers ;
                if(minAvgDist > avgDist) {
                    minAvgDist = avgDist ;
                    closest = enemy ;
                }
                avgDist = 0 ;
                numOfPlayers = 0 ;
            }
        }
        return closest ;
    }
    Character* SmartTeam::getNinjasTarget(Character *ninja, SmartTeam *targetTeam) {
        Character *currentCandidate = NULL;
        double min_dist = DBL_MAX;
        double current_dist = 0;
        int numOfDeadEnemies = 0 ;
        int numOfTargetedEnemies = 0 ;
        for(Character* enemy : targetTeam->characters){
            if (enemy->isAlive() && !is_targeted[enemy]) {
                current_dist = ninja->distance(enemy);
                if (current_dist < min_dist) {
                    min_dist = current_dist;
                    currentCandidate = enemy;
                }
            }else{
                if(!enemy->isAlive()){
                    numOfDeadEnemies++ ;
                }else{
                    numOfTargetedEnemies++ ;
                }
            }
        }
        if(currentCandidate == NULL) {
            if(numOfTargetedEnemies > 0){
                return findMinDist(ninja, *targetTeam) ;
            }else{
                return NULL ;
            }
        }
        is_targeted[currentCandidate] = true ;
        return currentCandidate ;
    }


///----- Ctor -----
    SmartTeam::SmartTeam(Character *leader) : leader(leader), size(1) {
        this->leader = leader;
        add(leader);
    }

///----- Dtor -----
    SmartTeam::~SmartTeam() {}

///----- Add character to the team, if the character is a cowboy instance, add to the cowboys vector, otherwise, -----
///----- add to the ninjas vector.                                                                               -----
    void SmartTeam::add(Character *character) {
        if(character->isPartOfTeam()){
            throw logic_error("Failed adding member to the team, the member is already in a team.") ;
        }
        if (size <= 10) {
            characters.push_back(character);
            size++;
            locations.push_back(&character->getLocation()) ;
        } else {
            throw range_error("Failed adding character, reached maximum amount of players in a team (10).");
        }
    }

    Character* SmartTeam::findWeakestMember(Character* ninja) {
        Character *weakestCowboy = NULL, *weakestNinja = NULL ;
        int minNinjaHP = 150, minCowboyHP = 120, numOfDead = 0 ;
        for(Character* character: characters) {
            if(character->isAlive()) {
                if (character != ninja) {
                    Ninja *testPtr = dynamic_cast<Ninja *>(ninja);
                    if (testPtr == nullptr) {
                        if (character->getHitPoints() < minCowboyHP) {
                            weakestCowboy = character ;
                        } else if (character->getHitPoints() == weakestCowboy->getHitPoints()) {
                            weakestCowboy = (ninja->distance(character) < ninja->distance(weakestCowboy)) ? character : weakestCowboy ;
                        }
                    } else {
                        if (character->getHitPoints() < minNinjaHP) {
                            weakestNinja = character ;
                        } else if (character->getHitPoints() == weakestNinja->getHitPoints()) {
                            weakestNinja = (ninja->distance(character) < ninja->distance(weakestNinja)) ? character : weakestNinja ;
                        }
                    }
                }
            }else {
                numOfDead++;
            }
        }
        if(numOfDead == size) {
            return NULL;
        }else {
            if (weakestCowboy != NULL) {
                return weakestCowboy;
            } else {
                return weakestNinja;
            }
        }
    }
    void SmartTeam::cowboysAttack(SmartTeam *targetTeam){
        for(Character* cowboy : characters){
            if(cowboy->isAlive()) {
                Cowboy *testPtr = dynamic_cast<Cowboy *>(cowboy);
                if (testPtr != nullptr) {
                    if(cowboysTarget == NULL || cowboysTarget->getHitPoints() <= 40){
                        cowboysTarget = getCowboysTarget(targetTeam) ;
                        if(cowboysTarget == NULL){
                            return ;
                        }
                    }
                    cowboy->attack(cowboysTarget) ;
                }
            }
        }
    }

    void SmartTeam::guard(Character* character) {
        Ninja *ninja = dynamic_cast<Ninja *>(ninja);
        if(ninjasGuards[character] == NULL) {
            return;
        }
        ninja->move(ninjasGuards[ninja]) ;
    }

    void SmartTeam::ninjasAttack(SmartTeam *targetTeam){
        Character* currentTarget = NULL ;
        for(Character* ninja : characters) {
            if (ninja->isAlive()) {
                Ninja * testPtr = dynamic_cast<Ninja *>(ninja);
                if (testPtr != nullptr) {
                    if(is_healthy(ninja)) {
                        currentTarget = getNinjasTarget(ninja, targetTeam);
                        if (currentTarget != NULL) {
                            ninja->attack(getNinjasTarget(ninja, targetTeam));
                        }
                    }
                    else{
                        if(ninjasGuards[ninja] == NULL) {
                            ninjasGuards[ninja] = findWeakestMember(ninja) ;
                        }else if(!ninjasGuards[ninja]->isAlive()) {
                            ninjasGuards[ninja] = findWeakestMember(ninja);
                        }else {
                            guard(ninja);
                        }
                    }
                }
            }
        }
    }
///----- Attack a given target team, each character will attack (if it can) the closest character to the current -----
///----- team leader, if in some of the teams there is no living characters left the do nothing.                 -----
void SmartTeam::attack(SmartTeam *targetTeam) {

    //----- If one of the teams have no living characters, the game is over -----
    if (stillAlive() == 0 || targetTeam->stillAlive() == 0) {
        return;
    }

    //----- If the current leader is dead, set the closest living character to the new leader -----
    if (!leader->isAlive()) {
        setNextLeader();
    }

        cowboysAttack(targetTeam) ;
        ninjasAttack(targetTeam) ;
}

///----- Returns the number of living members left on the team -----
int SmartTeam::stillAlive() {
    int count = 0;
    for (Character *character: characters) {
        if (character->isAlive()) {
            count++;
        }
    }
    return count;
}

///----- Sets the next leader when a current leader has died (The leader will be the closest member to the dead leader) -----
void SmartTeam::setNextLeader() {
    leader = findMinDist(leader, *this);
}

void SmartTeam::print() {
    for (Character *character: characters) {
        character->print();
    }
}
}