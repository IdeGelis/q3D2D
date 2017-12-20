#ifndef CCCALIBRATION_H
#define CCCALIBRATION_H

//CCLib
#include <Matrix.h>
#include <CCGeom.h>

class ccCalibration
{
public:
    ccCalibration();
protected:
    CCLib::MatrixTpl<Scalar> ppa;
    double focale;
    std::vector<double> sizeImg;
    CCLib::MatrixTpl<Scalar> pps;
    std::vector<double> distorsionCoefs;
    std::vector<double> drmax;
    double angleShot;
    //std::doubl empriseMax;
};

#endif // CCCALIBRATION_H
