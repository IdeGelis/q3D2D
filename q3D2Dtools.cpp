//System
#include <iostream>

//3D2D
#include "ccOrientation.h"
#include "ccCalibration.h"

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
    std::cout<<"Reading Xml"<<std::endl;

    // QXmlStreamReader oriFile = QXmlStreamReader(oriFiles.at(i));cc
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
        return;
    }


    //Place the orientation parametters in the right type
    QStringList centreCoord = centre.split(' ');
    Vector3Tpl<double> sommetPriseVue(centreCoord.at(0).toDouble(),centreCoord.at(1).toDouble(),centreCoord.at(2).toDouble());

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
    std::cout<<"Reading Xml"<<std::endl;

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
    QString distorsionCoefs = QString("test");


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
                        else if(reader.name() == "SzImg"){
                            sizeImg = reader.readElementText();
                        }
                        else if(reader.name() == "CalibDistorsion"){
                            while(reader.readNextStartElement()){
                                if(reader.name() == "ModRad"){
                                    while(reader.readNextStartElement()){
                                        if(reader.name() == "CDist"){
                                            pps = reader.readElementText();
                                        }
                                        else if(reader.name() == "CoeffDist"){
                                            distorsionCoefs = reader.readElementText();
                                        }
//                                        else if(reader.name() == "L2"){
//                                            l2 = reader.readElementText();
//                                        }
//                                        else if(reader.name() == "L2"){
//                                            l2 = reader.readElementText();
//                                        }
                                        else
                                            reader.skipCurrentElement();
                                    }
                                }

                            }
                        }
                    }
                 }
             }
        }
        else
            reader.raiseError(QObject::tr("Incorrect file"));
    }
    file.close();

    if (ppa == "test" || focale == "test" || sizeImg == "test" || pps == "test" || distorsionCoefs == "test"){
        std::cout << "File not conform!" << std::endl;
        QMessageBox msgBox;
        msgBox.setText("Orientation file" + filePath +" not conform");
        msgBox.exec();
    }
    std::cout<<ppa.toStdString()<<std::endl;
    std::cout<<focale.toStdString()<<std::endl;
    std::cout<<sizeImg.toStdString()<<std::endl;
    std::cout<<distorsionCoefs.toStdString()<<std::endl;

}
