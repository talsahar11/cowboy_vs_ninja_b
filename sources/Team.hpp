#ifndef COWBOY_VS_NINJA_A_TEAM_H
#define COWBOY_VS_NINJA_A_TEAM_H
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"
#include "Cowboy.hpp"
#include <vector>
namespace ariel {
    class Team {
    private:
        int size;
        Character *leader;
        vector<Character *> cowboys;
        vector<Character *> ninjas;

        void setNextLeader();

        friend Character *findMinDist(Character *source, Team *team);

    public:
        Team(Character *leader);

        ~Team();

        void add(Character *character);

        void attack(Team *targetTeam);

        int stillAlive();

        void print();

        Character *getLeader();
    };
}
#endif