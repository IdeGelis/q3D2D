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
    //std::cout<<!file.open(QFile::ReadOnly | QFile::Text)<<std::endl;
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        std::cout << "Cannot read file" << std::endl;
        exit(0);
    }

    QXmlStreamReader reader(&file);

    if (reader.readNextStartElement()) {
        std::cout<<reader.name().toString().toStdString()<<std::endl;
        if (reader.name() == "ExportAPERO"){
            while(reader.readNextStartElement()){
                std::cout<<reader.name().toString().toStdString()<<std::endl;
                if(reader.name() == "OrientationConique"){
                    while(reader.readNextStartElement()){
                        std::cout<<reader.name().toString().toStdString()<<std::endl;
                        if(reader.name() == "FileInterne"){
                            QString s = reader.readElementText();
                            std::cout<<s.toStdString()<<std::endl;
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
            }
        }
        else
            reader.raiseError(QObject::tr("Incorrect file"));
    }





//    QDomDocument dom("mon_xml");

//    QFile xml_doc(filePath);

//    if(!xml_doc.open(QIODevice::ReadOnly))

//    {

//        QMessageBox::warning(this, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être ouvert. Vérifiez que le nom est le bon et que le document est bien placé");

//        return;

//    }

//    if (!dom.setContent(&xml_doc))

//    {

//     xml_doc.close();

//     QMessageBox::warning(this, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être attribué à l'objet QDomDocument.");

//     return;

//    }

//    QDomElement dom_element = dom.documentElement();

//    QDomNode noeud = dom_element.firstChild();

//    while(!noeud.isNull())

//    {

//        if(!dom_element.isNull())

//            QMessageBox::information(this, "Nom de la balise", "Le nom de la balise est " + dom_element.tagName());

//                noeud = noeud.nextSibling();

//    }
//    QFile xml(filePath);

//    xml.open(QIODevice::ReadOnly);
//    QXmlStreamReader xmlData(&xml);
//    while(!xmlData.atEnd() && !xmlData.hasError()) {
//        std::cout<<"oui"<<std::endl;
//        std::cout<<toString(xmlData.name()).toStdString()<<std::endl;
//        if(xmlData.readNext() == QXmlStreamReader::StartElement && xmlData.name() == "FileInterne") {
//            std::cout<<"oui"<<std::endl;
//            std::cout<<xmlData.readElementText().toStdString()<<std::endl;
//        }
//    }



//    QFile xmlFile = new QFile(filePath);
//            if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
//                    QMessageBox::critical(this,"Load XML File Problem",
//                    "Couldn't open "+filePath+" to load settings for download",
//                    QMessageBox::Ok);
//                    return;
//            }
//    QXmlStreamReader xmlReader = new QXmlStreamReader(xmlFile);


//    //Parse the XML until we reach end of it
//    while(!xmlReader->atEnd() && !xmlReader->hasError()) {
//            // Read next element
//            QXmlStreamReader::TokenType token = xmlReader->readNext();
//            //If token is just StartDocument - go to next
//            if(token == QXmlStreamReader::StartDocument) {
//                    continue;
//            }
//            //If token is StartElement - read it
//            if(token == QXmlStreamReader::StartElement) {

//                    if(xmlReader->name() == "FileInterne") {
//                            std::cout<<xmlReader->readElementText()<<std::endl;
//                            continue;
//                    }

////                    if(xmlReader->name() == "id") {
////                        qDebug() << xmlReader->readElementText();
////                    }
//            }
//    }

//    if(xmlReader->hasError()) {
//            QMessageBox::critical(this,
//            "xmlFile.xml Parse Error",xmlReader->errorString(),
//            QMessageBox::Ok);
//            return;
//    }

//    //close reader and flush file
//    xmlReader->clear();
//    xmlFile->close();
}
