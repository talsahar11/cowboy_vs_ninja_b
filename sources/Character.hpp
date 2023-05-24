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
        int hit_points;
        Point location;

    protected:

        Character(const Character& other) = default ;
        Character& operator=(const Character& other) = default ;
        Character(Character&& other)noexcept = default ;
        Character& operator=(Character&& other) noexcept = default ;
        Character(string const& name, Point location) ;

        void setHitPoints(int value) ;
        void setLocation(Point location) ;

    public:
        virtual ~Character() = default ;

        double distance(const Character *other) ;
        bool isAlive() const ;
        void hit(int value) ;
        virtual void attack(Character *target) = 0 ;
        virtual string print() ;

        Point &getLocation() ;
        string getName() ;
        int getHitPoints() const ;
        bool isPartOfTeam() const ;
        void setPartOfTeam() ;
    };
}
#endif