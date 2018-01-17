#ifndef CCPOINT_H
#define CCPOINT_H

//CCLib
#include <CCGeom.h>
#include <SquareMatrix.h>


class ccPoint
{
public:
    ccPoint();
    Vector3Tpl<double> coord;
    Vector3Tpl<double> normal;
};

#endif // CCPOINT_H
