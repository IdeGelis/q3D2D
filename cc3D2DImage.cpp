﻿//##########################################################################
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
#include "q3D2Dtools.h"

//Qt
#include <QImage>
#include <QPixmap>


cc3D2DImage::cc3D2DImage(QString _path,QString _name,ccOrientation _ori,ccCalibration _cali)
    :QPixmap(_path),name(_name), ori(_ori), calib(_cali)
{

}

void cc3D2DImage::setVectVisee()
{
    // Get the coordonate of the ppa in the working site frame : by the inversion of the image formula

    CCVector3 coordPpaWorkSiteFrame;
    CCVector2 tmp;


    //I(-1)
    tmp = this->calib.ppa*(1/this->calib.focale) - this->calib.ppa;

    //PI(-1)
    coordPpaWorkSiteFrame.z = this->ori.sommetPdV.z + 1;
    coordPpaWorkSiteFrame.x = coordPpaWorkSiteFrame.z * tmp.x;
    coordPpaWorkSiteFrame.y = coordPpaWorkSiteFrame.z * tmp.y;
    //coordPpaWorkSiteFrame.u;
    coordPpaWorkSiteFrame = multiply((this->ori.rotation.inv()),coordPpaWorkSiteFrame) + this->ori.sommetPdV;

    this->vectVisee = this->ori.sommetPdV - coordPpaWorkSiteFrame;

}

CCVector2 cc3D2DImage::formuleImg(ccPoint point)
{
    //Calculate the coordinates of the point in the image frame

    CCVector2 coordRepIm;
    CCVector3 tmp;

    tmp = multiply(this->ori.rotation, point.coord) - this->ori.sommetPdV;

    //PI
    coordRepIm.x = tmp.x/tmp.z;
    coordRepIm.y = tmp.y/tmp.z;

    //I
    // //!\\  double * CCVector does not exist!! Do CCVector * double
    coordRepIm = coordRepIm * this->calib.focale + this->calib.ppa;

    return coordRepIm;
}

CCVector2 cc3D2DImage::addDisto(CCVector2 coordIm)
{
    //addDisto return the coordinate where a radial distorsion has been added.

    CCVector2 coordImDisto;
    coordImDisto = this->calib.pps;

    double d2 = std::pow(coordIm[0]-this->calib.pps.x,2) + std::pow(coordIm[1]-this->calib.pps.y,2);
    double fact = 1 + this->calib.distorsionCoefs[0]*d2 + this->calib.distorsionCoefs[1]*d2 + this->calib.distorsionCoefs[0]*d2;
    // //!\\  double * CCVector does not exist!! Do CCVector * double
    coordImDisto = coordImDisto + (coordIm - this->calib.pps)*fact;
    return coordImDisto;
}
