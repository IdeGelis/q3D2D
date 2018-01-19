#ifndef Q3D2DTOOLS
#define Q3D2DTOOLS

//System
#include <vector>

// 3D2D
#include "ccOrientation.h"
#include "ccCalibration.h"
#include "cc3D2DImage.h"

//CClib
#include <CCGeom.h>
#include <SquareMatrix.h>

//Qt
#include <QString>

ccOrientation xmlToOri(QString filePath);
ccCalibration xmlToCali(QString filePath);
ccCalibration calibExistOrCreate(QString pathCali,std::vector<cc3D2DImage>  images,QString pathFolderOriCali);
CCVector3 multiply(CCLib::SquareMatrixd mat, CCVector3 vect);

#endif // Q3D2DTOOLS

