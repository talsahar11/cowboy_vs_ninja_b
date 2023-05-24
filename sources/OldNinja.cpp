#include "OldNinja.hpp"
namespace ariel {
    ///-----Ctor - sets the hp and the speed according to the type of the ninja-----
    OldNinja::OldNinja(const string &name, Point location) : Ninja(name, location) {
        setHitPoints(150) ;
        setSpeed(8) ;
    }
}