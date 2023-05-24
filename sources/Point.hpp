#ifndef COWBOY_VS_NINJA_A_POINT_H
#define COWBOY_VS_NINJA_A_POINT_H
#include <ostream>
namespace ariel {
    class Point {
    private:
        double x, y;
    public:
        Point(double xVal, double yVal) ;
        ~Point() = default ;
        Point(const Point& other) = default ;
        Point(Point&& other)noexcept = default ;
        Point& operator=(Point&& other) noexcept = default ;
        Point &operator=(const Point &other) = default ;

        double getX() const ;

        double getY() const ;

        double distance(const Point &other) const ;

        void print() ;

        bool operator==(const Point &other) const ;

        static Point moveTowards(const Point& /*srcPoint*/, const Point& /*destPoint*/, double distance) ;  // NOLINT


        friend std::ostream &operator<<(std::ostream &oStr, const Point &point) ;
    };
}
#endif
