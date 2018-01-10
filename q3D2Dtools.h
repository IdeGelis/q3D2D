#ifndef Q3D2DTOOLS
#define Q3D2DTOOLS

// 3D2D
#include "ccOrientation.h"
#include "ccCalibration.h"

//Qt
#include <QString>

ccOrientation xmlToOri(QString filePath);
ccCalibration xmlToCali(QString filePath);

#endif // Q3D2DTOOLS

