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
#include "ccCalibration.h"

//CCLib
#include <CCGeom.h>
#include <SquareMatrix.h>


ccCalibration::ccCalibration(Vector2Tpl<double> _ppa, Vector2Tpl<double> _pps, double _focale,
                             Vector2Tpl<int> _szIm, Vector3Tpl<double> _distorsionCoefs)
    : ppa(_ppa), pps(_pps), focale(_focale), szIm(_szIm), distorsionCoefs(_distorsionCoefs)
{

}

