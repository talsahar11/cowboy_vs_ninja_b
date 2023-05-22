#include "YoungNinja.hpp"
namespace ariel {
    YoungNinja::YoungNinja(const string &name, Point location) : Ninja(name, location) {
        Character::hit_points = 100;
        Ninja::speed = 14;
    }
}