#include "OldNinja.hpp"
namespace ariel {
    OldNinja::OldNinja(string name, Point location) : Ninja(name, location) {
        Character::hit_points = 150;
        Ninja::speed = 8;
    }
}