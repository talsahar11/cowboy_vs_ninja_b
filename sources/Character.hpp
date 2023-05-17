#include "Point.hpp"
#include <string>
#include <iostream>
#ifndef CHARACTER_H
#define CHARACTER_H
namespace ariel {
    using namespace std;

    class Character {
    protected:
        string name;
        Point location;
        int hit_points;
        bool isAssociated ;
    public:
        Character(string name, Point location);

        bool isAlive();

        double distance(const Character *other);

        Point &getLocation();

        string getName();

        int getHitPoints() const;

        void decreaseHitPoints(int value);

        virtual string print();

        virtual void attack(Character *target) = 0;

        void setPartOfTeam() ;

        bool isPartOfTeam() ;

    };
}
#endif