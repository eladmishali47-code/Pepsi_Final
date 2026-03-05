#include "Point.h"

Point::Point(position pos, double uMass)
: _pos(pos), _dMass(uMass) {}

double Point::getMass() const
{
    return _dMass;
}

const position &Point::getPosition() const
{
    return _pos;
}

bool Point::operator==(const Point &other)
{
    return _pos == other._pos && _dMass == other._dMass;
}
