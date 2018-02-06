#ifndef CCCALIBRATION_H
#define CCCALIBRATION_H

//CCLib
#include <CCGeom.h>
#include <SquareMatrix.h>

class ccCalibration
{
public:
    ccCalibration(CCVector2 _ppa, CCVector2 _pps, double _focale, CCVector2 _szIm, CCVector3 _distorsionCoefs );

    CCVector3 distorsionCoefs;
    CCVector2 ppa;
    CCVector2 pps;
    CCVector2 szIm;
    double focale;

};

#endif // CCCALIBRATION_H
