#ifndef CC3D2DIMAGE_H
#define CC3D2DIMAGE_H

#include <string>

//CCLib
#include <Matrix.h>
#include <CCGeom.h>

//Qt
#include <QImage>

//3D2D
#include "ccCalibration.h"
#include "ccOrientation.h"


class cc3D2DImage : public QImage
{
public:
    cc3D2DImage();
    void setVectVisee();
    Vector2Tpl<float> addDisto(Vector2Tpl<float>);
    Vector2Tpl<float> formuleImg(Vecto2Tpl<float>);

protected:
    std::string name;
    ccCalibration calib;
    ccOrientation ori;
    Vector2Tpl<float> vectVisee;
};

#endif // CC3D2DIMAGE_H
