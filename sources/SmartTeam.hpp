#ifndef COWBOY_VS_NINJA_A_SMARTTEAM_H
#define COWBOY_VS_NINJA_A_SMARTTEAM_H
#include "Team.hpp"
#include <map>
namespace ariel {
    class SmartTeam: public Team {
    private:
        Character *cowboysTarget ;
        map<Character*, Character*> ninjasTargets ;
        map<Character*, Character*> ninjasGuards ;
        Character* getCowboysTarget(Team *targetTeam) ;
        void cowboysAttack(Team *targetTeam) ;
        void ninjasAttack(Team *targetTeam) ;
        void updateNinjasTargets(Team* targetTeam) ;
        void findAndSetTarget(Character* character, Team* targetTeam) ;
        bool isTargeted(Character* enemy);



            public:
        SmartTeam(Character *leader) ;

        void attack(Team *targetTeam) override ;

        void print() override ;
    };
}
#endif
