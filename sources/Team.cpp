#include "Team.hpp"
#include <cfloat>
namespace ariel {

    ///----- Ctor -----
    Team::Team(Character *leader) : leader(leader), size(1) {
        this->leader = leader;
        add(leader);
    }

    ///----- Dtor -----
    Team::~Team() {
        for(Character* character: characters){
            delete character ;
        }
    }

    ///----- Given a character and a team, this method returns the team`s character that is closest to the source character     -----
    ///----- (Without including the character himself). this method being used on findNewLeader function and on attack function -----
    Character* Team::findMinDist(Character *target, Team *team) {
        Character *currentCandidate = NULL;
        double min_dist = DBL_MAX;
        double current_dist = 0;

        //----- Iterate over the cowboy characters and get the min distance from the given character into the candidate -----
        for (Character *character: team->characters) {
            if (target != character) {
                if (character->isAlive()) {
                    current_dist = character->distance(target);
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

    ///----- Add character to the team, if the character is a cowboy instance, add to the cowboys vector, otherwise, -----
    ///----- add to the ninjas vector.                                                                               -----
    void Team::add(Character *character) {
        if(character->isPartOfTeam()){
            throw std::runtime_error("Failed adding member to the team, the member is already in a team.") ;
        }
        if (size <= 10) {
            character->setPartOfTeam() ;
            characters.push_back(character) ;
            size++;
        } else {
            throw range_error("Failed adding character, reached maximum amount of players in a team (10).");
        }

    }

    ///----- Attack a given target team, each character will attack (if it can) the closest character to the current -----
    ///----- team leader, if in some of the teams there is no living characters left do nothing.                     -----
    void Team::attack(Team *targetTeam) {
        if(targetTeam == nullptr){
            throw std::invalid_argument("Failed to attack - target team is nullptr.") ;
        }
        //----- If one of the teams have no living characters, the game is over -----
        if (stillAlive() == 0 || targetTeam->stillAlive() == 0) {
            throw std::runtime_error("Failed to attack, one of the teams are dead.") ;
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
        for (Character *character: characters) {
            if(character->isAlive()) {
                if (dynamic_cast<Cowboy *>(character) != nullptr) {
                    if (!target->isAlive()) {
                        target = findMinDist(leader, targetTeam);
                        if (target == NULL) {
                            return;
                        }
                    }
                    character->attack(target);
                }
            }
        }

        //----- If the ninja is close enough, slash the target, otherwise, move towards the target -----
        for (Character *character: characters) {
            if(character->isAlive()) {
                if (dynamic_cast<Ninja *>(character) != nullptr) {
                    if (!target->isAlive()) {
                        target = findMinDist(leader, targetTeam);
                        if (target == NULL) {
                            return;
                        }
                    }
                    character->attack(target);
                }
            }
        }
    }

    ///----- Returns the number of living members left on the team -----
    int Team::stillAlive() const{
        int count = 0;
        for (Character *character: characters) {
            if (character->isAlive()) {
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
        for(Character* character: characters){
            if (dynamic_cast<Cowboy *>(character) != nullptr) {
                std::cout << character->print() ;
            }
        }
        for(Character* character: characters){
            if (dynamic_cast<Ninja *>(character) != nullptr) {
                std::cout << character->print() ;
            }
        }
    }

    Character *Team::getLeader() {
        return leader;
    }

    void Team::increaseSize(){
        size++ ;
    }
    int Team::getSize() const{
        return size ;
    }
    vector<Character *> Team::getCharacters() const{
        return characters ;
    }
}
