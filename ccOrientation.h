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
    ccOrientation(Vector3Tpl<double> _sommetPdV, CCLib::SquareMatrixd _rotation, QString _pathCali);

    CCLib::SquareMatrixd rotation;
    Vector3Tpl<double> sommetPdV;
    QString pathCali;


/*    //Getter
    CCLib::SquareMatrixd getRotation();
    Vector3Tpl<double> getSommetPdV();
    QString getPathCali()*/;

};

#endif // CCORIENTATION_H
