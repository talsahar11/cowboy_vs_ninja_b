#include "Team.hpp"
#include <cfloat>
namespace ariel {
///----- Given a character and a team, this method returns the team`s character that is closest to the source character     -----
///----- (Without including the character himself). this method being used on findNewLeader function and on attack function -----
    Character *findMinDist(Character *character, Team *team) {
        Character *currentCandidate = NULL;
        double min_dist = DBL_MAX;
        double current_dist = 0;

        //----- Iterate over the cowboy characters and get the min distance from the given character into the candidate -----
        for (Character *cowboy: team->cowboys) {
            if (cowboy != character) {
                if (cowboy->isAlive()) {
                    current_dist = character->distance(cowboy);
                    if (current_dist < min_dist) {
                        min_dist = current_dist;
                        currentCandidate = cowboy;
                    }
                }
            }
        }

        //----- Iterate over the ninja characters and get the min distance from the given character into the candidate -----
        for (Character *ninja: team->ninjas) {
            if (ninja != character) {
                if (ninja->isAlive()) {
                    current_dist = character->distance(ninja);
                    if (current_dist < min_dist) {
                        min_dist = current_dist;
                        currentCandidate = ninja;
                    }
                }
            }
        }

        //----- Return the closest character -----
        return currentCandidate;
    }

///----- Ctor -----
    Team::Team(Character *leader) : leader(leader), size(1) {
        this->leader = leader;
        add(leader);
    }

///----- Dtor -----
    Team::~Team() {}

///----- Add character to the team, if the character is a cowboy instance, add to the cowboys vector, otherwise, -----
///----- add to the ninjas vector.                                                                               -----
    void Team::add(Character *character) {
        if(character->isPartOfTeam()){
            throw logic_error("Failed adding member to the team, the member is already in a team.") ;
        }
        if (size <= 10) {
            if (dynamic_cast<Ninja *>(character) != nullptr) {
                ninjas.push_back(character);
            } else {
                cowboys.push_back(character);
            }
            size++;
        } else {
            throw range_error("Failed adding character, reached maximum amount of players in a team (10).");
        }

    }

///----- Attack a given target team, each character will attack (if it can) the closest character to the current -----
///----- team leader, if in some of the teams there is no living characters left do nothing.                     -----
    void Team::attack(Team *targetTeam) {
        //----- If one of the teams have no living characters, the game is over -----
        if (stillAlive() == 0 || targetTeam->stillAlive() == 0) {
            return;
        }

        //----- If the current leader is dead, set the closest living character to the new leader -----
        if (!leader->isAlive()) {
            setNextLeader();
        }

        //----- Find the character from the target team that is the closest to the current team leader -----
        Character *target = findMinDist(leader, targetTeam);

        //----- Iterate over the cowboys and ninjas lists, if the target is dead from previous attacks, get the next -----
        //----- target, and if the character is able to hit the target, attack                                       -----

        //----- If the cowboy has no bullets, reload, otherwise, shoot the target -----
        for (Character *cowboy: cowboys) {
            if (!target->isAlive()) {
                target = findMinDist(leader, targetTeam);
            }
            cowboy->attack(target);
        }
        //----- If the ninja is close enough, slash the target, otherwise, move towards the target -----
        for (Character *ninja: ninjas) {
            if (!target->isAlive()) {
                target = findMinDist(leader, targetTeam);
            }
            ninja->attack(target);
        }
    }

///----- Returns the number of living members left on the team -----
    int Team::stillAlive() const{
        int count = 0;
        for (Character *cowboy: cowboys) {
            if (cowboy->isAlive()) {
                count++;
            }
        }
        for (Character *ninja: ninjas) {
            if (ninja->isAlive()) {
                count++;
            }
        }
        return count;
    }

///----- Sets the next leader when a current leader has died (The leader will be the closest member to the dead leader) -----
    void Team::setNextLeader() {
        leader = findMinDist(leader, this);
    }

    void Team::print() {
        for (Character *cowboy: cowboys) {
            cowboy->print();
        }
        for (Character *ninja: ninjas) {
            ninja->print();
        }
    }

    Character *Team::getLeader() {
        return leader;
    }
}