#ifndef CCCALIBRATION_H
#define CCCALIBRATION_H

//CCLib
//#include <MatrixXX.h>
//#include <CCGeom.h>

class ccCalibration
{
public:
    ccCalibration();
    void setAngleShot();
    void setDistoMax();
//    vectorTpl<float> calcDisto(vector2Tpl<float>);

protected:
//    CCLib::Matrix<> ppa;
//    double focale;
//    std::vector<double> sizeImg;
//    CCLib::MatrixTpl<Scalar> pps;
//    std::vector<double> distorsionCoefs;
//    std::vector<double> drmax;
    double angleShot;
    //std::doubl empriseMax;
};

#endif // CCCALIBRATION_H
