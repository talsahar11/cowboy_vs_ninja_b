#include "OldNinja.hpp"
namespace ariel {
    OldNinja::OldNinja(const string &name, Point location) : Ninja(name, location) {
        Character::hit_points = 150;
        Ninja::speed = 8;
    }
}