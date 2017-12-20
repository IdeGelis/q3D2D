#ifndef CCWORKSITE_H
#define CCWORKSITE_H

#include <string>
#include <vector>

#include "cc3D2DImage.h"


class ccWorkSite
{
public:
    ccWorkSite();

protected:
    std::string pathFolderImg;
    std::string pathFolderOriCali;
    std::vector<cc3D2DImage> images;
};

#endif // CCWORKSITE_H
