#include "Team2.hpp"
#include <cfloat>
namespace ariel {

    ///----- Ctor -----
    Team2::Team2(Character *leader) : Team(leader) {
    }

    ///----- Attack a given target team, each character will attack (if it can) the closest character to the current -----
    ///----- team leader, if in some of the teams there is no living characters left throw an exception.             -----
    void Team2::attack(Team *targetTeam) {
        if(targetTeam == nullptr){
            throw std::invalid_argument("Failed to attack - target team is nullptr.") ;
        }
        //----- If one of the teams have no living characters, the game is over -----
        if (stillAlive() == 0 || targetTeam->stillAlive() == 0) {
            throw std::runtime_error("Failed to attack, one of the teams are dead.") ;
        }

        //----- If the current leader is dead, set the closest living character to the new leader -----
        if (!getLeader()->isAlive()) {
            setNextLeader();
        }

        //----- Find the character from the target team that is the closest to the current team leader -----
        Character *target = findMinDist(getLeader(), targetTeam);

        //----- Iterate over the characters list and attack with each character, if the target is dead from -----
        //----- previous attacks, get the next target, and if there are no targets left, return.            -----
        for (Character *character: getCharacters()) {
            if(character->isAlive()) {
                if (!target->isAlive()) {
                    target = findMinDist(getLeader(), targetTeam);
                    if(target == NULL){
                        return ;
                    }
                }
                character->attack(target);
            }
        }
    }

    ///----- Print each member of the team -----
    void Team2::print() {
        for (Character *character: getCharacters()) {
            std::cout << character->print() ;
        }
    }
}