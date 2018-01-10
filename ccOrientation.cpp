//3D2D
#include "ccOrientation.h"

//CCLib
#include <CCGeom.h>
#include <SquareMatrix.h>


ccOrientation::ccOrientation(Vector3Tpl<double> _sommetPdV, CCLib::SquareMatrixd _rotation, QString _pathCali)
    :sommetPdV(_sommetPdV), rotation(_rotation), pathCali(_pathCali)
{

}

