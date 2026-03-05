#include "Simulation.h"
#include <map>
#include <math.h>

Simulation::Simulation(std::vector<Point> masses, double boxLength, Point pIndex)
: _vPoints(masses), _dBoxLength(boxLength), _pIndex(pIndex)
{      
    // If we have no points, return
    if (_vPoints.size() == 0) return;

    // If we have one point, define the center of mass as this point and return
    if(_vPoints.size() == 1) {
        _pCenterOfMass = _vPoints.back();
        return;
    }

    // Else, split the Points into SPLIT_FACTOR simulations
    _vSubSimulations.reserve(8);
    
    // Map each Point to its sub-simulation
    std::map<uint, std::vector<Point>> mPointToSimulation;
    for (const Point& p : _vPoints){
        // Determine the Points in this sub-cube
        uint index = 0;
        for (int dim = 0; dim < DIM_COUNT; dim++){
            // If p is larger than box length / 2 in this dimension
            if (p.getPosition().at(dim) >= _dBoxLength / 2) index = index | (1 << dim);
        }
        // Add p to its sub simulation list
        mPointToSimulation[index].emplace_back(p);
    }

    // Initalize each one of the sub-simulations
    std::vector<const Point*> vCentersOfMass; 
    for (int index = 0; index < mPointToSimulation.size(); index++){
        const auto& Points = mPointToSimulation[index];
        // Get the correct sub cube
        bool x = (index & 1), y = (index & 2) , z = (index & 4);
        // Define new box length
        double dNewBoxLength = _dBoxLength / 2;
        // Get new index
        Point pNewIndex({
            _pIndex.getPosition().at(0) + static_cast<int>(x) * dNewBoxLength,
            _pIndex.getPosition().at(0) + static_cast<int>(y) * dNewBoxLength,  
            _pIndex.getPosition().at(0) + static_cast<int>(z) * dNewBoxLength}, 0);
        
        // Initalize sub simulation
        _vSubSimulations.emplace_back(Simulation(Points, dNewBoxLength, pNewIndex));
        // Get center of mass
        vCentersOfMass.emplace_back(&_vSubSimulations.back());
    }

    double dTotalMass = 0;
    position pos = {0,0,0};
    for (int i = 0; i < vCentersOfMass.size(); i++){
        double dTotalMass = vCentersOfMass[i]->getMass();
        dTotalMass += dTotalMass;
        for (int j = 0; j < DIM_COUNT; j++){
            pos[j] += dTotalMass * vCentersOfMass[i]->getPosition().at(j);
        }
    }    
    for (int j = 0; j < DIM_COUNT; j++){
        pos[j] /= dTotalMass;
    }

    // Define center of mass
    _pCenterOfMass = Point(pos, dTotalMass);
}

double Simulation::getDiagonalLength() const
{
    return std::sqrt(DIM_COUNT) * _dBoxLength;
}

double Simulation::getBoxLength() const
{
    return _dBoxLength;
}

const Point& Simulation::getCenterOfMass() const
{
    return _pCenterOfMass;
}
