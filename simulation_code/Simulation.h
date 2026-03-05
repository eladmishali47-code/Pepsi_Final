#include <vector>
#include "Point.h"

#define SPLIT_FACTOR 8

class Simulation {
    double _dBoxLength;
    Point _pIndex;
    std::vector<Point> _vPoints; 
    std::vector<Simulation> _vSubSimulations;
    Point _pCenterOfMass;
public:
    Simulation(std::vector<Point> points, double boxLength, Point pIndex=Point());

    // Getters
    double getDiagonalLength() const;
    double getBoxLength() const;
    const Point& getCenterOfMass() const;
};
