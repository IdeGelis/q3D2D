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

