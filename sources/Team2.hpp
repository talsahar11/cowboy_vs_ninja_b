#ifndef COWBOY_VS_NINJA_A_TEAM2_H
#define COWBOY_VS_NINJA_A_TEAM2_H
#include "Team.hpp"
#include <vector>
namespace ariel {

    class Team2 :public Team {
    public:
        Team2(Character *leader) ;

        void attack(Team *targetTeam) override ;

        void print() override ;
    };
}
#endif