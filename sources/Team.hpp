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
        vector<Character *> characters;
    protected:
        void increaseSize() ;
        int getSize() const ;

        void setNextLeader() ;

        Character *findMinDist(Character *source, Team *team) ;

    public:
        Team(Character *leader);
        virtual ~Team() ;
        Team(const Team& other) = default ;
        Team& operator=(const Team& other) = default ;
        Team(Team&& other)noexcept = default ;
        Team& operator=(Team&& other) noexcept = default ;

        void add(Character *character) ;

        virtual void attack(Team *targetTeam) ;

        int stillAlive() const ;

        virtual void print() ;

        vector<Character *> getCharacters() const ;
        Character *getLeader() ;
    };
}
#endif