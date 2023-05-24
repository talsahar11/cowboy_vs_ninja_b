#include "SmartTeam.hpp"
#include <cfloat>
namespace ariel {

    ///----- Ctor -----
    SmartTeam::SmartTeam(Character *leader) : Team(leader) {}

    ///-----Chooses the closest enemy in average to all of the teammates and set it as the cowboys target-----
    Character* SmartTeam::getCowboysTarget(Team *targetTeam){
        Character* closest = NULL ;
        double cumulativeDistance = 0, avgDist = 0,minAvgDist = DBL_MAX ;
        int numOfPlayers = 0 ;
        for(Character* enemy: targetTeam->getCharacters()){
            if(enemy->isAlive()) {
                for (Character *teamPlayer: getCharacters()) {
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
                numOfPlayers = 0 ;
            }
        }
        return closest ;
    }

    ///-----Check if a given enemy is exists as value in the targets map-----
    bool SmartTeam::isTargeted(Character* enemy){
        for (const auto &pair: ninjasTargets) {
            if (pair.second == enemy) {
                return true;
            }
        }
        return false ;
    }

    ///-----Sets a target for a ninja, chooses the closest enemy to the ninja that have not been targeted yet, -----
    ///-----if there is no such enemy, the closest enemy will be chosen even if it is already been targeted    -----
    void SmartTeam::findAndSetTarget(Character* character, Team* targetTeam){
        Character* candidateTarget = NULL;
        double minDist = DBL_MAX, currentDist = 0 ;
        for(Character* enemy: targetTeam->getCharacters()) {
            if(!isTargeted(enemy) && enemy->isAlive()){
                currentDist = character->distance(enemy) ;
                if(currentDist < minDist){
                    minDist = currentDist ;
                    candidateTarget = enemy ;
                }
            }
        }
        if(candidateTarget == NULL){
            candidateTarget = findMinDist(character, targetTeam) ;
        }
        ninjasTargets[character] = candidateTarget ;
    }

    ///-----Before each ninjas attack, the targets map will be updated, if target is dead, the ninja which targeted-----
    ///-----it will find another target. if a ninja has died, the target will be removed from the targets map      -----
    void SmartTeam::updateNinjasTargets(Team *targetTeam) {
        for(Character* character: getCharacters()){
            if(character->isAlive()) {
                Ninja *testPtr = dynamic_cast<Ninja *>(character);
                if (testPtr != nullptr) {
                    if(ninjasTargets[character] == NULL){
                        findAndSetTarget(character, targetTeam) ;
                    }else if(!(ninjasTargets[character]->isAlive())){
                        findAndSetTarget(character, targetTeam) ;
                    }
                }
            }
        }
    }

    ///-----The ninjas will attack their targets, when each ninja have his own target, if the amount-----
    ///-----of targets is less then the ninjas available, then some of the enemies will be targeted -----
    ///-----by more of one ninja                                                                    -----
    void SmartTeam::ninjasAttack(Team *targetTeam) {
        updateNinjasTargets(targetTeam) ;
        for(Character* ninja: getCharacters()){
            if(ninja->isAlive()){
                Ninja *testPtr = dynamic_cast<Ninja *>(ninja);
                if (testPtr != nullptr) {
                    ninja->attack(ninjasTargets[ninja]) ;
                }
            }
        }
    }

    ///-----Cowboys attack - each cowboy will attack the enemy that is most close to all teammates in average-----
    ///-----The cowboys target will be changed if the target is dead, or have less then 40 hit points        -----
    void SmartTeam::cowboysAttack(Team *targetTeam){
        for(Character* cowboy : getCharacters()){
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

    ///----- Attack a given target team, each character will attack (if it can) the closest character to the current -----
    ///----- team leader, if in some of the teams there is no living characters left the do nothing.                 -----
    void SmartTeam::attack(Team *targetTeam) {

        //----- If one of the teams have no living characters, the game is over -----
        if (stillAlive() == 0 || targetTeam->stillAlive() == 0) {
            return;
        }

        //----- If the current leader is dead, set the closest living character to the new leader -----
        if (!getLeader()->isAlive()) {
            setNextLeader();
        }

        cowboysAttack(targetTeam) ;
        ninjasAttack(targetTeam) ;
    }

    ///-----Print each member of the team-----
    void SmartTeam::print() {
        for (Character *character: getCharacters()) {
            std::cout << character->print() ;
        }
    }
}