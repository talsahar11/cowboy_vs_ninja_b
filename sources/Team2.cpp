#include "Team2.hpp"
#include <cfloat>
namespace ariel {

///----- Given a character and a team, this method returns the team`s character that is closest to the source character     -----
///----- (Without including the character himself). this method being used on findNewLeader function and on attack function -----
    Character *findMinDist(Character *source, Team2 &team) {
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

///----- Ctor -----
    Team2::Team2(Character *leader) : leader(leader), size(1) {
        this->leader = leader;
        add(leader);
    }

///----- Dtor -----
    Team2::~Team2() {}

///----- Add character to the team, if the character is a cowboy instance, add to the cowboys vector, otherwise, -----
///----- add to the ninjas vector.                                                                               -----
    void Team2::add(Character *character) {
        if(character->isPartOfTeam()){
            throw logic_error("Failed adding member to the team, the member is already in a team.") ;
        }
        if (size <= 10) {
            characters.push_back(character);
            size++;
        } else {
            throw range_error("Failed adding character, reached maximum amount of players in a team (10).");
        }
    }

///----- Attack a given target team, each character will attack (if it can) the closest character to the current -----
///----- team leader, if in some of the teams there is no living characters left the do nothing.                 -----
    void Team2::attack(Team2 *targetTeam) {

        //----- If one of the teams have no living characters, the game is over -----
        if (stillAlive() == 0 || targetTeam->stillAlive() == 0) {
            return;
        }

        //----- If the current leader is dead, set the closest living character to the new leader -----
        if (!leader->isAlive()) {
            setNextLeader();
        }

        //----- Find the character from the target team that is the closest to the current team leader -----
        Character *target = findMinDist(leader, *targetTeam);

        //----- Iterate over the characters list, if the target is dead from previous attacks, get the next -----
        //----- target, and if the character is able to hit the target, attack                              -----

        //----- If the cowboy has no bullets, reload, otherwise, shoot the target -----
        for (Character *character: characters) {
            if (!target->isAlive()) {
                target = findMinDist(leader, *targetTeam);
            }
            std::cout << character->getName() << " Attacking: " << target->getName() << "with hp: " << target->getHitPoints() << std::endl;
            character->attack(target);
        }
    }

///----- Returns the number of living members left on the team -----
    int Team2::stillAlive() const {
        int count = 0;
        for (Character *character: characters) {
            if (character->isAlive()) {
                count++;
            }
        }
        return count;
    }

///----- Sets the next leader when a current leader has died (The leader will be the closest member to the dead leader) -----
    void Team2::setNextLeader() {
        leader = findMinDist(leader, *this);
    }

    void Team2::print() {
        for (Character *character: characters) {
            character->print();
        }
    }
}