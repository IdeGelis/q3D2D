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
    coordPpaWorkSiteFrame.z = this->ori.sommetPdV.z + 1.0;
    coordPpaWorkSiteFrame.x = coordPpaWorkSiteFrame.z * tmp.x;
    coordPpaWorkSiteFrame.y = coordPpaWorkSiteFrame.z * tmp.y;
    //coordPpaWorkSiteFrame.u;
    coordPpaWorkSiteFrame = multiply((this->ori.rotation.transposed()),coordPpaWorkSiteFrame) + this->ori.sommetPdV;

    this->vectVisee = this->ori.sommetPdV - coordPpaWorkSiteFrame;
    //std::cout<<this->vectVisee.x<<" "<<this->vectVisee.y<<" "<<this->vectVisee.z<<std::endl;
    this->vectVisee.normalize();
    //std::cout<<this->vectVisee.x<<" "<<this->vectVisee.y<<" "<<this->vectVisee.z<<std::endl;


}

CCVector2 cc3D2DImage::formuleImg(ccPoint point)
{
    //Calculate the coordinates of the point in the image frame

    CCVector2 coordRepIm;
    CCVector3 tmp;

    // R*(pt - SPdV)
    tmp = point.coord - this->ori.sommetPdV;

    tmp = multiply(this->ori.rotation.transposed(), tmp);

    //PI
    coordRepIm.x = tmp.x/tmp.z;
    coordRepIm.y = tmp.y/tmp.z;

    //I : PPA + F*(u,v)
    // //!\\  double * CCVector does not exist!! Do CCVector * double
    coordRepIm = coordRepIm * this->calib.focale + this->calib.ppa;

    return coordRepIm;
}

CCVector2 cc3D2DImage::addDisto(CCVector2 coordIm)
{
    //addDisto return the coordinate where a radial distorsion has been added.

    CCVector2 coordImDisto;

    //d2 = squarred distance
    double d2 = std::pow(coordIm.x-this->calib.pps.x,2) + std::pow(coordIm.y-this->calib.pps.y,2);

    //METHODE ANTOINE
    double fact = this->calib.distorsionCoefs.x*d2 + this->calib.distorsionCoefs.y*(std::pow(d2,2)) + this->calib.distorsionCoefs.z*(std::pow(d2,3));

    coordImDisto.x = (coordIm.x - this->calib.pps.x)*fact + coordIm.x;
    coordImDisto.y = (coordIm.y - this->calib.pps.y)*fact + coordIm.y;
    return coordImDisto;
}
