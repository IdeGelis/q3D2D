#ifndef CCCALIBRATION_H
#define CCCALIBRATION_H

//CCLib
#include <CCGeom.h>
#include <SquareMatrix.h>

class ccCalibration
{
public:
    ccCalibration(Vector2Tpl<double> _ppa, Vector2Tpl<double> _pps, double _focale, Vector2Tpl<int> _szIm, Vector3Tpl<double> _distorsionCoefs );
    void setAngleShot();
    void setDistoMax();
//    vectorTpl<float> calcDisto(vector2Tpl<float>);

protected:
    Vector3Tpl<double> distorsionCoefs;
    Vector2Tpl<double> ppa;
    Vector2Tpl<double> pps;
    Vector2Tpl<int> szIm;
    double focale;
//    std::vector<double> drmax;
    double angleShot;
    //std::doubl empriseMax;
};

#endif // CCCALIBRATION_H
