#include <vector>
#include <memory>
#include <array>
#include "Point.h"

#define SPLIT_FACTOR 8

class Simulation {
    double _dBoxLength;
    Point _pIndex;
    std::vector<Point> _vPoints; 
    std::vector<Simulation> _vSubSimulations;
    Point _pCenterOfMass;
    uint _uTotalOfMass;
public:
    Simulation(std::vector<Point> masses, double boxLength, Point pIndex);

    // Getters
    double getDiagonalLength() const;
    double getBoxLength() const;
    const Point& getCenterOfMass() const;
};
