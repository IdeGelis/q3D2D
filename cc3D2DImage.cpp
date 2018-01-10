//System
#include <iostream>

//3D2D
#include "cc3D2DImage.h"
#include "ccOrientation.h"

//Qt
#include <QImage>

cc3D2DImage::cc3D2DImage(QString _path,QString _name,ccOrientation _orientation)
    :QImage(_path),name(_name), ori(_orientation)
{
   // std::cout<<"Creating cc3D2DImage object"<<std::endl;
}

