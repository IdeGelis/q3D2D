//System
#include <iostream>
#include <vector>

//3D2D
#include "q3D2Dtools.h"
#include "ccWorkSite.h"
#include "cc3D2DImage.h"
#include "ccOrientation.h"

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
    std::vector<cc3D2DImage> images;

    // Cross all the orientation folder to create cc3D2DImage object for each image having an orientation file
    for (int i = 0; i < oriFiles.size(); ++i){
        std::cout<<oriFiles.at(i).toStdString()<<std::endl;

        //Image's name is contained in the orientation file's name
        // Orientation file name : "Orientation-IMAGENAME.xml"
        //                         "-12 letters-IMAGENAME-4 letters"
        int nbCaractFileName = oriFiles.at(i).size() - (12+4);
        QString imgName = oriFiles.at(i).mid(12,nbCaractFileName);
        QString pathImg = pathFolderImg + "/" + imgName;

        //Creation of the ccOrientation object
        ccOrientation ori = xmlToOri(pathFolderOriCali + "/" + oriFiles.at(i));


        //Test if the ccCalibration object corresponding to caliFile has already been created
        // if not create the object
        ccCalibration cali = calibExistOrCreate(ori.pathCali, images, pathFolderOriCali);


        // Creation of the cc3D2DImage object
        cc3D2DImage img(pathImg,imgName,ori,cali);

        images.push_back(img);

    }

//    for(int unsigned i=0;i<images.size();i++){
//        std::cout<< images[i].name.toStdString()<<std::endl;
//    }


}
