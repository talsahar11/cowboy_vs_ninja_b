#include "Point.hpp"
#include <math.h>
#include <iostream>
#include <iomanip>
namespace ariel {
    using namespace std;

    ///-----Ctor-----
    Point::Point(double x, double y) : x(x), y(y) {}

    ///-----Operator = overloading-----
    bool Point::operator==(const Point &other) const {
        if (x == other.x && y == other.y) {
            return true;
        }
        return false;
    }


    ///-----Return the distance between the current instance and another point-----
    double Point::distance(const Point &other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }

    ///-----Move a given point towards a destination point, return the point that is most close to the dest point-----
    ///-----by moving the source point to a length of the given distance or less                                 -----
    Point Point::moveTowards(const Point &src, const Point &dest, double distance) {
        if(distance <= 0){
            throw std::invalid_argument("Failed to move towards with a non positive distance value.") ;
        }
        if (src == dest) {
            return src;
        }
        double dx = dest.x - src.x;
        double dy = dest.y - src.y;
        double dist_points = src.distance(dest);
        double unit_x = dx / dist_points;
        double unit_y = dy / dist_points;
        return Point(src.x + unit_x * min(dist_points, distance), src.y + unit_y * min(dist_points, distance));
    }

    ///-----Adding a string of the point to an ostream-----
    std::ostream &operator<<(std::ostream &os, const Point &current) {
        os << "(" << current.getX() << "," << current.getY() << ")";
        return os;
    }

    ///-----Print the point in a format of (x,y)-----
    void Point::print() {
        cout << std::setprecision(10) << "(" << x << ", " << y << ")" << endl;
    }

    ///-----Getters-----

    double Point::getX() const { return x; }

    double Point::getY() const { return y; }
}