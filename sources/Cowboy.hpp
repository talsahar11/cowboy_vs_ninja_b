#include "Character.hpp"
#ifndef COWBOY_VS_NINJA_A_COWBOY_H
#define COWBOY_VS_NINJA_A_COWBOY_H
namespace ariel {
    class Cowboy : public Character {
    private:
        int amount_of_bullets;
    public:
        Cowboy(string name, Point location);

        void shoot(Character *target);

        bool hasBullets();

        void reload();

        string print();

        void attack(Character *target);
    };
}
#endif