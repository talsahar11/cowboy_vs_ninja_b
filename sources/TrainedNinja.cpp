#include "TrainedNinja.hpp"
namespace ariel {
    TrainedNinja::TrainedNinja(const string &name, Point location) : Ninja(name, location) {
        Character::hit_points = 120;
        Ninja::speed = 12;
    }
}