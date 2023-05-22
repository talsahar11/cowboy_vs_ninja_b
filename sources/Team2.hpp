#ifndef COWBOY_VS_NINJA_A_TEAM2_H
#define COWBOY_VS_NINJA_A_TEAM2_H
#include "Team.hpp"
#include <vector>
namespace ariel {

    class Team2 :public Team {
    private:
        int size;
        Character *leader;
        vector<Character *> characters;

        void setNextLeader() ;

        friend Character *findMinDist(Character *source, Team2 &team) ;

    public:
        Team2(Character *leader) ;
        Team2(const Team2& other) = default ;
        Team2& operator=(const Team2& other) = default ;
        Team2(Team2&& other)noexcept = default ;
        Team2& operator=(Team2&& other) noexcept = default ;
        ~Team2() ;

        void add(Character *character) ;

        void attack(Team2 *targetTeam) ;

        int stillAlive() const ;

        void print() ;
    };
}
#endif