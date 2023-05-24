#include "Character.hpp"
#ifndef COWBOY_VS_NINJA_A_NINJA_H
#define COWBOY_VS_NINJA_A_NINJA_H
namespace ariel {
    class Ninja : public Character {
    private:
        int speed;
    protected:
        void setSpeed(int value) ;
        int getSpeed() const ;
    public:
        Ninja(const string &name, Point location) ;
        ~Ninja() override = default ;
        Ninja(const Ninja& other) = default ;
        Ninja& operator=(const Ninja& other) = default ;
        Ninja(Ninja&& other)noexcept = default ;
        Ninja& operator=(Ninja&& other) noexcept = default ;
        void move(Character *target) ;

        void slash(Character *target) ;

        string print() override ;

        void attack(Character *target) override ;
    };
}
#endif