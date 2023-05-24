#include "Character.hpp"
#ifndef COWBOY_VS_NINJA_A_COWBOY_H
#define COWBOY_VS_NINJA_A_COWBOY_H
namespace ariel {
    class Cowboy : public Character {
    private:
        int amount_of_bullets;
    public:
        ~Cowboy() override = default ;
        Cowboy(const Cowboy& other) = default ;
        Cowboy& operator=(const Cowboy& other) = default ;
        Cowboy(Cowboy&& other)noexcept = default ;
        Cowboy& operator=(Cowboy&& other) noexcept = default ;
        Cowboy(const string &name, Point location) ;

        void shoot(Character *target) ;

        bool hasboolets() const ;

        void reload() ;

        string print() override ;

        void attack(Character *target) override ;
    };
}
#endif