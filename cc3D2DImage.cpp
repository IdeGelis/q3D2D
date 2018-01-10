//System
#include <iostream>

//3D2D
#include "cc3D2DImage.h"
#include "ccOrientation.h"
#include "ccCalibration.h"

//Qt
#include <QImage>

cc3D2DImage::cc3D2DImage(QString _path,QString _name,ccOrientation _ori,ccCalibration _cali)
    :QImage(_path),name(_name), ori(_ori), calib(_cali)
{
   // std::cout<<"Creating cc3D2DImage object"<<std::endl;
}

