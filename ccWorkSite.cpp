//System
#include <iostream>

//3D2D
#include "ccWorkSite.h"

//Qt
#include <QString>
#include <QDir>

ccWorkSite::ccWorkSite(QString _pathFolderImg, QString _pathFolderOriCali)
    :pathFolderImg(_pathFolderImg), pathFolderOriCali(_pathFolderOriCali)
{
}
//ccWorkSite::ccWorkSite(std::string _pathFolderImg, std::string _pathFolderOriCali)
//    :pathFolderImg(_pathFolderImg), pathFolderOriCali(_pathFolderOriCali)
//{
//}

void ccWorkSite::initialise()
{
    // initialise() is going to create all cc3D2DImages object
    // with the link to the calibration and orientation information
    std::cout<<"Initializing..."<<std::endl;

    //Create QDir objects to access folders
    QDir dirImg  = QDir(this->pathFolderImg);
    QDir dirParam  = QDir(this->pathFolderOriCali);

    //QStringList dirImgContent = dirImg.entryList(QDir::Files);


    //QStringList dirParamContent = dirParam.entryList(QDir::Files); cc

    //Selection of all orientation files
    QStringList filters;
    filters<<"Orientation*";
    dirParam.setNameFilters(filters);
    QStringList oriFiles = dirParam.entryList(QDir::Files);


    for (int i = 0; i < oriFiles.size(); ++i){
        std::cout<<oriFiles.at(i).toStdString()<<std::endl;
       // QXmlStreamReader oriFile = QXmlStreamReader(oriFiles.at(i));cc
    }
    //https://stackoverflow.com/questions/3092387/parse-a-xml-file-in-qt

}
