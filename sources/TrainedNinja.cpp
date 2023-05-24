#include "TrainedNinja.hpp"
namespace ariel {

    ///-----Ctor - sets the hp and the speed according to the type of the ninja-----
    TrainedNinja::TrainedNinja(const string &name, Point location) : Ninja(name, location) {
        setHitPoints(120) ;
        setSpeed(12) ;
    }
}