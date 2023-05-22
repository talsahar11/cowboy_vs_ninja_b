#include "Point.hpp"
#include <string>
#include <iostream>
#ifndef CHARACTER_H
#define CHARACTER_H
namespace ariel {
    using namespace std;

    class Character {
    private:
        string name;
        bool isAssociated ;

    protected:
        ~Character() = default ;
        Character(const Character& other) = default ;
        Character& operator=(const Character& other) = default ;
        Character(Character&& other)noexcept = default ;
        Character& operator=(Character&& other) noexcept = default ;
        Character(string const& name, Point location) ;
        int hit_points;
        Point location;


    public:
        Point &getLocation() ;
        string getName() ;
        int getHitPoints() const ;
        double distance(const Character *other) ;
        bool isAlive() const ;
        bool isPartOfTeam() const ;
        void setPartOfTeam() ;
        void hit(int value) ;
        virtual string print() ;
        virtual void attack(Character *target) = 0 ;
    };

}
#endif