#include "YoungNinja.hpp"
namespace ariel {

    ///-----Ctor - sets the hp and the speed according to the type of the ninja-----
    YoungNinja::YoungNinja(const string &name, Point location) : Ninja(name, location) {
        setHitPoints(100) ;
        setSpeed(14) ;
    }
}