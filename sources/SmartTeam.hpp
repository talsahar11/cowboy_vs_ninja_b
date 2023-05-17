#ifndef COWBOY_VS_NINJA_A_SMARTTEAM_H
#define COWBOY_VS_NINJA_A_SMARTTEAM_H
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"
#include "Cowboy.hpp"
#include <vector>
#include <map>
namespace ariel {
    class SmartTeam {
    private:
        int size;
        Character *leader;
        Character *cowboysTarget ;
        vector<Character *> characters;
        vector<Point*> locations ;
        void setNextLeader();
        map<Character*, bool> is_targeted ;
        map<Character*, Character*> ninjasGuards ;
        friend Character *findMinDist(Character *source, SmartTeam &team);
        Character* getCowboysTarget(SmartTeam *targetTeam) ;
        Character* getNinjasTarget(Character *ninja, SmartTeam *targetTeam) ;
        void cowboysAttack(SmartTeam *targetTeam) ;
        void ninjasAttack(SmartTeam *targetTeam) ;
        Character* findWeakestMember(Character *ninja) ;
        void guard(Character* ninja) ;
    public:
        SmartTeam(Character *leader);

        ~SmartTeam();

        void add(Character *character);

        void attack(SmartTeam *targetTeam);

        int stillAlive();

        void print();


        vector<Character*> getCharacters(){
            return characters ;
        }
    };
}
#endif
