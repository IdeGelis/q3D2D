//System
#include <iostream>

//3D2D
#include "ccOrientation.h"

//Qt
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>
#include <QStringRef>

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
    QString calibPath;
    QString l1;
    QString l2;
    QString l3;


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
                                if(reader.name() == "ParamRotation"){
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


    std::cout<<calibPath.toStdString()<<std::endl;
    std::cout<<l1.toStdString()<<std::endl;
    std::cout<<l2.toStdString()<<std::endl;
    std::cout<<l3.toStdString()<<std::endl;
}
