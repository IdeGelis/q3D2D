//##########################################################################
//#                                                                        #
//#                       CLOUDCOMPARE PLUGIN: q3D2D                       #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#                             COPYRIGHT: ENSG Iris de Gelis              #
//#                                                                        #
//##########################################################################

//System
#include <iostream>
#include <vector>
#include <iomanip>

//3D2D
#include "ccOrientation.h"
#include "ccCalibration.h"
#include "cc3D2DImage.h"

//Qt
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QMessageBox>

//CClib
#include <CCGeom.h>
#include <SquareMatrix.h>


ccOrientation xmlToOri(QString filePath)
{
    // xmlToOri is able to read an xml of orientation and to return a ccOrientation object
    // made of this orientation file
    //std::cout<<"Reading Xml"<<std::endl;

    QFile file(filePath);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        std::cout << "Cannot read file" << std::endl;
        exit(0);
    }

    QXmlStreamReader reader(&file);

    //Element to import
    QString calibPath = QString("test");
    QString centre = QString("test");
    QString l1 = QString("test");
    QString l2 = QString("test");
    QString l3 = QString("test");


    if (reader.readNextStartElement()) {

        if (reader.name() == "ExportAPERO"){
            while(reader.readNextStartElement()){

                if(reader.name() == "OrientationConique"){
                    while(reader.readNextStartElement()){

                        if(reader.name() == "FileInterne"){
                            calibPath = reader.readElementText();
                        }

                        else if(reader.name() == "Externe"){
                            while(reader.readNextStartElement()){
                                if(reader.name() == "Centre"){
                                    centre = reader.readElementText();
                                }
                                else if(reader.name() == "ParamRotation"){
                                    while(reader.readNextStartElement()){
                                        if(reader.name() == "CodageMatr"){
                                            while(reader.readNextStartElement()){
                                                if(reader.name() == "L1"){
                                                    l1 = reader.readElementText();
                                                }
                                                else if(reader.name() == "L2"){
                                                    l2 = reader.readElementText();
                                                }
                                                else if(reader.name() == "L3"){
                                                    l3 = reader.readElementText();
                                                }
                                                else
                                                    reader.skipCurrentElement();
                                            }
                                        }
                                        else
                                            reader.skipCurrentElement();
                                    }
                                }
                                else
                                    reader.skipCurrentElement();
                            }
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else
                    reader.skipCurrentElement();
            }
        }
        else
            reader.raiseError(QObject::tr("Incorrect file"));
    }
    file.close();

    if (calibPath == "test" || centre == "test" || l1 == "test" || l2 == "test" || l3 == "test"){
        std::cout << "File not conform!" << std::endl;
        QMessageBox msgBox;
        msgBox.setText("Orientation file" + filePath +" not conform");
        msgBox.exec();

    }


    //Place the orientation parametters in the right type
    QStringList centreCoord = centre.split(' ');
    std::cout.precision(18);

    CCVector3 sommetPriseVue(centreCoord.at(0).toDouble(),centreCoord.at(1).toDouble(),centreCoord.at(2).toDouble());

    CCLib::SquareMatrixd rotation(3);

    QStringList l1List = l1.split(' ');
    for (int i=0;i<3;i++){
        rotation.setValue(0,i,l1List.at(i).toDouble());
    }
    QStringList l2List = l2.split(' ');
    for (int i=0;i<3;i++){
        rotation.setValue(1,i,l2List.at(i).toDouble());
    }
    QStringList l3List = l3.split(' ');
    for (int i=0;i<3;i++){
        rotation.setValue(2,i,l3List.at(i).toDouble());
    }

    //Create the ccOrientation object
    ccOrientation ori(sommetPriseVue,rotation,calibPath);
    return ori;
}


ccCalibration xmlToCali(QString filePath)
{
    // xmlToOri is able to read an xml of orientation and to return a ccOrientation object
    // made of this orientation file
    //std::cout<<"Reading Xml"<<std::endl;

    // QXmlStreamReader oriFile = QXmlStreamReader(oriFiles.at(i));cc
    QFile file(filePath);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        std::cout << "Cannot read file" << std::endl;
        exit(0);
    }

    QXmlStreamReader reader(&file);

    //Element to import
    QString ppa = QString("test");
    QString focale = QString("test");
    QString pps = QString("test");
    QString sizeImg = QString("test");
    QString distorsionCoefs1 = QString("test");
    QString distorsionCoefs2;
    QString distorsionCoefs3;

    if (reader.readNextStartElement()) {

        if (reader.name() == "ExportAPERO"){
            while(reader.readNextStartElement()){
                if(reader.name() == "CalibrationInternConique"){
                    while(reader.readNextStartElement()){
                        if(reader.name() == "PP"){
                            ppa = reader.readElementText();
                        }
                        else if(reader.name() == "F"){
                            focale = reader.readElementText();
                        }
                        else if(reader.name() == "SzIm"){
                            sizeImg = reader.readElementText();
                        }
                        else if(reader.name() == "CalibDistortion"){
                            while(reader.readNextStartElement()){
                                if(reader.name() == "ModRad"){
                                    int cpt = 1;
                                    while(reader.readNextStartElement()){
                                        std::cout<<reader.name().toString().toStdString()<<std::endl;

                                        if(reader.name() == "CDist"){
                                            pps = reader.readElementText();
                                        }
                                        else if(reader.name() == "CoeffDist" && cpt == 1){
                                            distorsionCoefs1 = reader.readElementText();
                                            cpt +=1;
                                        }
                                        else if(reader.name() == "CoeffDist" && cpt == 2){

                                            distorsionCoefs2 = reader.readElementText();
                                            cpt +=1;
                                        }
                                        else if(reader.name() == "CoeffDist" && cpt == 3){

                                            distorsionCoefs3 = reader.readElementText();
                                            cpt +=1;
                                        }
                                        else
                                            reader.skipCurrentElement();
                                    }
                                }
                                else
                                    reader.skipCurrentElement();

                            }
                        }
                        else
                            reader.skipCurrentElement();
                    }
                 }
                else
                    reader.skipCurrentElement();
             }
        }
        else
            reader.raiseError(QObject::tr("Incorrect file"));
    }
    file.close();

    if (ppa == "test" || focale == "test" || sizeImg == "test" || pps == "test" || distorsionCoefs1 == "test"){
        std::cout << "File not conform!" << std::endl;
        QMessageBox msgBox;
        msgBox.setText("Orientation file" + filePath +" not conform");
        msgBox.exec();
    }

    //Place the calibration parametters in the right type
    QStringList ppaCoord = ppa.split(' ');
//    Vector2Tpl<double> ppaVect(ppaCoord.at(0).toFloat(), ppaCoord.at(1).toFloat());
    CCVector2 ppaVect(ppaCoord.at(0).toDouble(), ppaCoord.at(1).toDouble());

    double foc = focale.toDouble();

    QStringList szImList = sizeImg.split(' ');
    CCVector2 szIm(szImList.at(0).toInt(), szImList.at(1).toInt());

    QStringList ppsCoord = pps.split(' ');
    CCVector2 ppsVect(ppsCoord.at(0).toDouble(), ppsCoord.at(1).toDouble());

    CCVector3 coefDisto(distorsionCoefs1.toDouble(),distorsionCoefs2.toDouble(),distorsionCoefs3.toDouble());
    ccCalibration cali(ppaVect,ppsVect,foc,szIm,coefDisto);
    return cali;

}


ccCalibration calibExistOrCreate(QString pathCali,std::vector<cc3D2DImage>  images, QString pathFolderOriCali)
{
    // calibExistOrCreate test if the ccCalibration given in the file pathCali already exists
    // If it exists calibExistOrCreate return this ccCalibration object otherwise it creates this object

    int nbIm = images.size();

    for (int i=0; i<nbIm; i++){
       // if (QString::compare(pathCali, images.at(i).ori.pathCali)==0){
        if (pathCali == images.at(i).ori.pathCali) {
            return images.at(i).calib;
        }
    }

    //If it attempts here, it means that the ccCalibration object associated to pathCali doesn't exist
    //So we need to create it from the XML file
    QStringList pathCal = pathCali.split('/');
    QString caliFile = pathCal.at(pathCal.size()-1);
    ccCalibration cali = xmlToCali(pathFolderOriCali + "/" + caliFile);

    return cali;
}


CCVector3 multiply(CCLib::SquareMatrixd mat, CCVector3 vect)
{
    CCVector3 res;
    res.x = mat.getValue(0,0)*vect.x + mat.getValue(0,1)*vect.y + mat.getValue(0,2)*vect.z;
    res.y = mat.getValue(1,0)*vect.x + mat.getValue(1,1)*vect.y + mat.getValue(1,2)*vect.z;
    res.z = mat.getValue(2,0)*vect.x + mat.getValue(2,1)*vect.y + mat.getValue(2,2)*vect.z;

    return res;
}
