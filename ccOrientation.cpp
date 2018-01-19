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

//3D2D
#include "ccOrientation.h"

//CCLib
#include <CCGeom.h>
#include <SquareMatrix.h>


//ccOrientation::ccOrientation(Vector3Tpl<double> _sommetPdV, CCLib::SquareMatrixd _rotation, QString _pathCali)
//    :sommetPdV(_sommetPdV), rotation(_rotation), pathCali(_pathCali)
//{

//}
ccOrientation::ccOrientation(CCVector3 _sommetPdV, CCLib::SquareMatrixd _rotation, QString _pathCali)
    :sommetPdV(_sommetPdV), rotation(_rotation), pathCali(_pathCali)
{

}

//CCLib::SquareMatrixd ccOrientation::getRotation()
//{
//    return this->rotation;
//}

//Vector3Tpl<double> ccOrientation::getSommetPdV()
//{
//    return this->sommetPdV;
//}

//QString ccOrientation::getPathCali()
//{
//    return this->pathCali;
//}
