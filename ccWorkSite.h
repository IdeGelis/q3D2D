#ifndef CCWORKSITE_H
#define CCWORKSITE_H

// System
#include <string>
#include <vector>

// 3D2D
#include "cc3D2DImage.h"

//Qt
#include <QString>


class ccWorkSite
{
public:
    ccWorkSite();
    void initialise(QString _pathFolderImg, QString _pathFolderOriCali);

//protected:
    QString pathFolderImg;
    QString pathFolderOriCali;
    std::vector<cc3D2DImage> images;
    std::vector<cc3D2DImage> selectedImgs;
};

#endif // CCWORKSITE_H
