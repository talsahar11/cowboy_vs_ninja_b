#include "Cowboy.hpp"
namespace ariel {
    Cowboy::Cowboy(string name, Point location) : Character(name, location) {
        amount_of_bullets = 6;
        hit_points = 110;
    }

    void Cowboy::shoot(Character *target) {
        if (Character::isAlive() && hasBullets()) {
            target->decreaseHitPoints(10);
            amount_of_bullets--;
        }
    }

    bool Cowboy::hasBullets() { return (amount_of_bullets > 0); }

    void Cowboy::reload() { amount_of_bullets = 6; }

    void Cowboy::attack(Character *target) {
        if (isAlive()) {
            if (hasBullets()) {
                shoot(target);
            } else {
                reload();
            }
        }
    }

    string Cowboy::print() {
        return "C " + Character::print();
    }
}