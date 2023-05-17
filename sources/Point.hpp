#ifndef COWBOY_VS_NINJA_A_POINT_H
#define COWBOY_VS_NINJA_A_POINT_H
#include <ostream>
namespace ariel {
    class Point {
    private:
        double x, y;
    public:
        Point(double x, double y);

        Point &operator=(const Point &other) {
            if (this != &other) { // check for self-assignment
                x = other.x;
                y = other.y;
            }
            return *this;
        }

        double getX() const;

        double getY() const;

        double distance(const Point &other) const;

        void print();

        bool operator==(const Point &other) const;

        friend Point moveTowards(const Point &src, const Point &dest, double distance);

        friend std::ostream &operator<<(std::ostream &os, const Point &point);
    };
}
#endif
