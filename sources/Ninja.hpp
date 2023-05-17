#include "Character.hpp"
#ifndef COWBOY_VS_NINJA_A_NINJA_H
#define COWBOY_VS_NINJA_A_NINJA_H
namespace ariel {
    class Ninja : public Character {
    protected:
        int speed;
    public:
        Ninja(string name, Point location);

        void move(Character *target);

        void slash(Character *target);

        string print();

        void attack(Character *target);
    };
}
#endif