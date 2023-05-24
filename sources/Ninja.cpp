#include "Ninja.hpp"
namespace ariel {

    ///-----Ctor-----
    Ninja::Ninja(const string &name, Point location) : Character(name, location) {}

    ///-----Move towards a given target. if the ninja is dead, throw exception-----
    void Ninja::move(Character *target) {
        if(isAlive()) {
            setLocation(Point::moveTowards(getLocation(), target->getLocation(), speed));
        }else{
            throw std::runtime_error("Attack failed - dead characters cannot attack.") ;
        }
    }

    ///-----Slash a given target and decrease its hp by 40-----
    void Ninja::slash(Character *target) {

        //-----If the ninja and the target are the same object, or the ninja or the target are dead, throw an-----
        //-----exception. Otherwise if the target distance from the ninja is less than 1, attack             -----
        if(target == this){
            throw std::runtime_error("Character cannot attack itself.") ;
        }else if (isAlive() && target->isAlive()) {
            if (getLocation().distance(target->getLocation()) < 1) {
                target->hit(40);
            }
        }else{
            throw std::runtime_error("Attack failed - dead characters cannot attack.") ;
        }
    }

    ///-----Attacking a given target. If distance is less than 1, slash the target, otherwise, move towards it-----
    void Ninja::attack(Character *target) {
        if (distance(target) < 1) {
            slash(target);
        } else {
            move(target);
        }
    }

    ///-----Print the data of the ninja instance-----
    string Ninja::print() {
        return "N " + Character::print() ;
    }

    ///-----Getters-----
    void Ninja::setSpeed(int value){
        speed = value ;
    }
    int Ninja::getSpeed() const{
        return speed ;
    }
}