#include "Character.hpp"
#include <iomanip>
namespace ariel {

    ///-----Ctor-----
    Character::Character(const string &name, Point location) : name(name), location(location), isAssociated(false) {}
    bool Character::isAlive() const {
        return (hit_points > 0);
    }

    ///-----Calculate the distance between the current character and another character instance-----
    double Character::distance(const Character *other) {
        return location.distance(other->location);
    }

    ///-----Decrease the hp on the current characters-----
    void Character::hit(int value) {
        //-----If the value to decrease is negative or the current character is already dead, throw an exception-----
        if(value < 0){
            throw std::invalid_argument("Cannot hit a character with a negative value.") ;
        }else if(hit_points == 0){
            throw std::runtime_error("Hit failed - cannot hit a dead character.") ;
        }

        //-----Reduce the hp of the character by the given value, the hp cannot get below zero-----
        int reduced_hp = hit_points - value;
        hit_points = (reduced_hp < 0) ? 0 : reduced_hp;
    }


    ///-----Print each member of the team, if character is alive, print its hp, else ignore it-----
    string Character::print() {
        std::ostringstream oss;
        if (isAlive()) {
            oss << name << ", " << hit_points << ", " << location << "\n";
        } else {
            oss << '(' << name << ')' << ", " << location << "\n" ;
        }
        return oss.str();
    }

    ///-----Getters and setters-----
    Point &Character::getLocation() {
        return location;
    }

    string Character::getName() {
        return name;
    }

    void Character::setHitPoints(int value){
        hit_points = value ;
    }
    int Character::getHitPoints() const { return hit_points; }

    void Character::setLocation(Point location){
        this->location = location ;
    }

    void Character::setPartOfTeam() {
        isAssociated = true ;
    }

    bool Character::isPartOfTeam() const {
        return isAssociated ;
    }
}