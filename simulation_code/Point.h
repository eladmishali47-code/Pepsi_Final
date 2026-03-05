#include <array>
#include <memory>

#define DIM_COUNT 3
#define uint uint32_t
#define position std::array<double, DIM_COUNT>

class Point{
    position _pos;
    double _dMass;
public:
    Point(position pos={0,0,0}, double uMass=0);
    double getMass() const;
    const position& getPosition() const;
    bool operator==(const Point& p);
};