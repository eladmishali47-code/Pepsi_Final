#include <array>

#define DIM_COUNT 3
#define uint uint32_t
#define position std::array<int, DIM_COUNT>

class Point{
    position _pos;
    uint _uMass;
public:
    Point(position pos, uint uMass);
    uint getMass() const;
    const position& getPosition() const;
};