#ifndef CCORIENTATION_H
#define CCORIENTATION_H

//CCLib
#include <CCGeom.h>
#include <SquareMatrix.h>

//Qt
#include <QString>


class ccOrientation
{
public:
    ccOrientation(Vector3Tpl<double> _sommetPdV, CCLib::SquareMatrixd _rotation);
private:
    CCLib::SquareMatrixd rotation;
    Vector3Tpl<double> sommetPdV;
    QString pathCali;
};

#endif // CCORIENTATION_H
