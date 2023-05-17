#include "YoungNinja.hpp"
namespace ariel {
    YoungNinja::YoungNinja(string name, Point location) : Ninja(name, location) {
        Character::hit_points = 100;
        Ninja::speed = 14;
    }
}