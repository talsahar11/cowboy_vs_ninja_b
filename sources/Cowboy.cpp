#include "Cowboy.hpp"
namespace ariel {

    ///-----Ctor-----
    Cowboy::Cowboy(const string &name, Point location) : Character(name, location) {
        amount_of_bullets = 6;
        setHitPoints(110) ;
    }

    ///-----Shoot a character, decrease its hp by 10-----
    void Cowboy::shoot(Character *target) {

        //-----If the character tries to shoot itself or one of the characters isn't alive, throw an exception,
        //-----else, check if there are bullets left to shoot, and if there is, shoot-----
        if(target == this){
            throw std::runtime_error("Character cannot attack itself.") ;
        }else if (isAlive() && target->isAlive()) {
            if (hasboolets()) {
                target->hit(10);
                amount_of_bullets--;
            }
        }else{
            throw std::runtime_error("Attack failed - dead characters cannot attack.") ;
        }
    }

    ///-----Check if there are bullets left to shoot-----
    bool Cowboy::hasboolets() const{
        return (amount_of_bullets > 0);
    }

    ///-----Restore the bullets amount to 6-----
    void Cowboy::reload() {

        //-----If the cowboy is dead, throw exception-----
        if(!isAlive()){
            throw std::runtime_error("Dead cowboy cannot reload.") ;
        }
        amount_of_bullets = 6 ;
    }

    ///-----Attack a given target, if the cowboy have bullets left, shoot the target. otherwise, reload-----
    void Cowboy::attack(Character *target) {
        if (hasboolets()) {
            shoot(target);
        } else {
            reload();
        }
    }

    ///-----Print the cowboy details-----
    string Cowboy::print() {
        return "C " + Character::print();
    }
}