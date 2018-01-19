#ifndef CC3D2DIMAGE_H
#define CC3D2DIMAGE_H

//System

//CCLib
#include <CCGeom.h>
#include <SquareMatrix.h>

//Qt
#include <QImage>
#include <QString>

//3D2D
#include "ccCalibration.h"
#include "ccOrientation.h"
#include "ccPoint.h"


class cc3D2DImage : public QImage
{
public:
    cc3D2DImage(QString _path, QString _name, ccOrientation _ori, ccCalibration _cali);

    void setVectVisee();
//    Vector2Tpl<float> addDisto(Vector2Tpl<float>);
//    Vector2Tpl<float> formuleImg(Vecto2Tpl<float>);

//public:
    QString name;
    ccCalibration calib;
    ccOrientation ori;
//    Vector3Tpl<double> vectVisee;
    CCVector3 vectVisee;

    Vector2Tpl<double> formuleImg(ccPoint point);
    //Vector2Tpl<double> addDisto(Vector2Tpl coordIm);
};

#endif // CC3D2DIMAGE_H
