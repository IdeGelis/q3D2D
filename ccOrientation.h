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
    ccOrientation(CCVector3 _sommetPdV, CCLib::SquareMatrixd _rotation, QString _pathCali);

    CCLib::SquareMatrixd rotation;
    CCVector3 sommetPdV;
    QString pathCali;

};

#endif // CCORIENTATION_H
