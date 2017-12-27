//System
#include <iostream>

//3D2D
#include "ccWorkSite.h"

//Qt
#include <QString>


ccWorkSite::ccWorkSite(QString _pathFolderImg, QString _pathFolderOriCali)
    :pathFolderImg(_pathFolderImg), pathFolderOriCali(_pathFolderOriCali)
{
}

ccWorkSite::initialise()
{
    std::cout<<"Initializing..."<<std::endl;
}
