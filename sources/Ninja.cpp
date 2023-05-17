#include "Ninja.hpp"
namespace ariel {
    Ninja::Ninja(string name, Point location) : Character(name, location) {}

    void Ninja::move(Character *target) {
        location = moveTowards(location, target->getLocation(), speed);
    }

    void Ninja::slash(Character *target) {
        if (Character::isAlive() && location.distance(target->getLocation()) < 1) {
            target->decreaseHitPoints(40);
        }
    }

    void Ninja::attack(Character *target) {
        if (isAlive()) {
            if (distance(target) < 1) {
                slash(target);
            } else {
                move(target);
            }
        }
    }

    string Ninja::print() {
        return "N " + Character::print() ;
    }
}