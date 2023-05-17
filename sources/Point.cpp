#include "Point.hpp"
#include <math.h>
#include <iostream>
#include <iomanip>
namespace ariel {
    using namespace std;

    Point::Point(double x, double y) : x(x), y(y) {}

    bool Point::operator==(const Point &other) const {
        if (x == other.x && y == other.y) {
            return true;
        }
        return false;
    }

    double Point::getX() const { return x; }

    double Point::getY() const { return y; }

    double Point::distance(const Point &other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }

    Point moveTowards(const Point &src, const Point &dest, double distance) {
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

    std::ostream &operator<<(std::ostream &os, const Point &current) {
        os << "(" << current.getX() << "," << current.getY() << ")";
        return os;
    }

    void Point::print() {
        cout << std::setprecision(10) << "(" << x << ", " << y << ")" << endl;
    }
}