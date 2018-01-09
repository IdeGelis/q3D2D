//System
#include <iostream>

//3D2D
#include "ccWorkSite.h"
#include "cc3D2DImage.h"

//Qt
#include <QString>
#include <QDir>
#include <QImage>

ccWorkSite::ccWorkSite(QString _pathFolderImg, QString _pathFolderOriCali)
    :pathFolderImg(_pathFolderImg), pathFolderOriCali(_pathFolderOriCali)
{
}

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

    // Cross all the orientation folder to create ccq3D2DImage object for each image having an orientation file
    for (int i = 0; i < oriFiles.size(); ++i){
        std::cout<<oriFiles.at(i).toStdString()<<std::endl;

        //Image's name is contained in the orientation file's name
        // Orientation file name : "Orientation-IMAGENAME.xml"
        //                         "-12 letters-IMAGENAME-4 letters"
        int nbCaractFileName = oriFiles.at(i).size() - (12+4);
        QString imgName = oriFiles.at(i).mid(12,nbCaractFileName);

        QString pathImg = pathFolderImg + "/" + imgName;


        //QImage Img = QImage(pathImg);

        //std::cout<<pathImg.toStdString()<<std::endl;

       // QXmlStreamReader oriFile = QXmlStreamReader(oriFiles.at(i));cc
    }
    //https://stackoverflow.com/questions/3092387/parse-a-xml-file-in-qt

}
