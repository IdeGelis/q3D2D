//##########################################################################
//#                                                                        #
//#                       CLOUDCOMPARE PLUGIN: q3D2D                       #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#                             COPYRIGHT: ENSG Iris de Gelis              #
//#                                                                        #
//##########################################################################

//System
#include <iostream>

//CCLib
#include <CCGeom.h>
#include <SquareMatrix.h>

//3D2D
#include "cc3D2DImage.h"
#include "ccOrientation.h"
#include "ccCalibration.h"
#include "ccPoint.h"

//Qt
#include <QImage>

cc3D2DImage::cc3D2DImage(QString _path,QString _name,ccOrientation _ori,ccCalibration _cali)
    :QImage(_path),name(_name), ori(_ori), calib(_cali)
{

}

void cc3D2DImage::setVectVisee()
{
    // Get the coordonate of the ppa in the working site frame : by the inversion of the image formula
//    Vector3Tpl<double> coordPpaWorkSiteFrame;
//    Vector2Tpl<double> tmp;


//    //I(-1)
//    tmp = this->calib.ppa*(1/this->calib.focale) - this->calib.ppa;

//    //PI(-1)
//    coordPpaWorkSiteFrame[2] = this->ori.sommetPdV[2] + 1;
//    coordPpaWorkSiteFrame[0] = coordPpaWorkSiteFrame[2] * tmp[0];
//    coordPpaWorkSiteFrame[1] = coordPpaWorkSiteFrame[2] * tmp[1];

//    coordPpaWorkSiteFrame = (this->ori.rotation.inv())*coordPpaWorkSiteFrame + this->ori.sommetPdV;

//    this->vectVisee = this->ori.sommetPdV - coordPpaWorkSiteFrame;

}

//Vector2Tpl<double> cc3D2DImage::formuleImg(ccPoint point)
//{
//    //Calculate the coordinates of the point in the image frame

////    Vector2Tpl<double> coordRepIm;
////    Vector2Tpl<double> tmp;

////    tmp = this->ori.rotation * point.coord - this->ori.sommetPdV;

////    //PI
////    coordRepIm[0] = tmp[0]/tmp[2];
////    coordRepIm[1] = tmp[1]/tmp[2];

////    //I
////    coordRepIm = this->calib.focale * coordRepIm + this->calib.ppa;

////    return coordRepIm;
//}

//Vector2Tpl<double> cc3D2DImage::addDisto(Vector2Tpl coordIm)
//{
//    //addDisto return the coordinate where a radial distorsion has been added.

////    Vector2Tpl<double> coordImDisto;

////    coordImDisto = this->calib.pps;
////    double d2 = (coordIm[0]-this->calib.pps[0])**2 + (coordIm[1]-this->calib.pps[1])**2;
////    double fact = 1 + this->calib.distorsionCoefs[0]*d2 + this->calib.distorsionCoefs[1]*d2 + this->calib.distorsionCoefs[0]*d2;

////    coordImDisto = coordImDisto + fact*(coordIm - this->calib.pps);
////    return coordImDisto;
//}
