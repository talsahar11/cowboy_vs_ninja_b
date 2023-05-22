#include "Character.hpp"
#include <iomanip>
namespace ariel {
    Character::Character(const string &name, Point location) : name(name), location(location), isAssociated(false) {}

    bool Character::isAlive() const {
        return (hit_points > 0);
    }

    double Character::distance(const Character *other) {
        return location.distance(other->location);
    }

    Point &Character::getLocation() { return location; }

    string Character::getName() { return name; }

    string Character::print() {
        std::ostringstream oss;
        if (isAlive()) {
            oss << name << ", " << hit_points << ", " << location << "\n";
        } else {
            oss << '(' << name << ')' << ", " << location << "\n" ;
        }
        return oss.str();
    }

    void Character::hit(int value) {
        if(value < 0){
            throw std::invalid_argument("Cannot hit a character with a negative value.") ;
        }
        int reduced_hp = hit_points - value;
        hit_points = (reduced_hp < 0) ? 0 : reduced_hp;
    }

    int Character::getHitPoints() const { return hit_points; }

    void Character::setPartOfTeam() {
        isAssociated = true ;
    }

    bool Character::isPartOfTeam() const {
        return isAssociated ;
    }
}