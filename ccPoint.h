#ifndef CCPOINT_H
#define CCPOINT_H

//CCLib
#include <CCGeom.h>
#include <SquareMatrix.h>


class ccPoint
{
public:
    ccPoint();
    CCVector3 coord;
    CCVector3 normal;
};

#endif // CCPOINT_H
