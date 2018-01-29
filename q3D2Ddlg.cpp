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
#include <string>
#include <typeinfo>
#include <vector>

//3D2D
#include "ccWorkSite.h"
#include "q3D2Ddlg.h"
#include "ui_q3D2Ddlg.h"
#include "ccPoint.h"
#include "cc3D2DImage.h"
#include "q3D2DDisplayImgDlg.h"
#include "q3D2DDispIm.h"

//Qt
#include "qfiledialog.h"
#include <QString>
#include <QDir>
#include <QXmlStreamReader>
#include <QListWidgetItem>
#include <QImageReader>

//qCC
#include <ccGLWindow.h>
#include "ccPickingHub.h"
#include "ccMainAppInterface.h"
#include "ccPickingListener.h"


q3D2DDlg::q3D2DDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::q3D2DDlg)
{
    ui->setupUi(this);

    this->currentWorkSite = new ccWorkSite();

    this->currentPoint = new ccPoint();

    ui->push_reproj->setEnabled(true);

    //Connexion of butons
    QObject::connect(ui->push_load,SIGNAL(released()),this,SLOT(load()));
    QObject::connect(ui->push_slctPt,SIGNAL(released()),this,SLOT(selectPt()));
    QObject::connect(ui->push_reproj,SIGNAL(released()),this,SLOT(reproj()));
    QObject::connect(ui->push_display,SIGNAL(released()),this,SLOT(displayImg()));

}

q3D2DDlg::~q3D2DDlg()
{
    delete ui;
}

void q3D2DDlg::load()
{
    // Loading of folders containing the images and the XML files of parameters
    std::cout<<"Loading folders containning images and files of parameters..."<<std::endl;

    //QDir::homePath() : In order to be able work on several computer and several environment
    QString dirImgStr = QFileDialog::getExistingDirectory(this, tr("Select Images Directory"),
                                                               QDir::homePath(),
                                                               QFileDialog::ShowDirsOnly
                                                               | QFileDialog::DontResolveSymlinks);

    // Parameters folder is usually the same as images folder
    QString dirParamStr = QFileDialog::getExistingDirectory(this, tr("Select the folder containing parameters files"),
                                                         QDir(dirImgStr).absolutePath(),
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);

    this->currentWorkSite->initialise(dirImgStr,dirParamStr);
    ui->label_img->setText(dirImgStr);
    ui->label_param->setText(dirParamStr);
    ui->push_slctPt->setEnabled(true);

}


void q3D2DDlg::selectPt()
{
    std::cout<<"Selecting mode"<<std::endl;
    //http://www.cloudcompare.org/forum/viewtopic.php?t=514
    //std::cout<<typeid(this->app).name()<<std::endl;
    this->m_pickingHub = this->m_app->pickingHub();

    //m_pickingHub->togglePickingMode(true);
    this->m_pickingHub->addListener(this,true,true);

}

//This function is called when a point is picked (through the picking hub)
void q3D2DDlg::onItemPicked(const ccPickingListener::PickedItem& pi)
{

    pointPicked(pi.entity, pi.itemIndex, pi.clickPoint.x(), pi.clickPoint.y(), pi.P3D); //map straight to pointPicked function
}

//Process point picks
void q3D2DDlg::pointPicked(ccHObject* entity, unsigned itemIdx, int x, int y, const CCVector3& P)
{
    if (!entity) //null pick
    {
        return;
    }

    ui->label_x->setText(QString::number(P.x));
    ui->label_y->setText(QString::number(P.y));
    ui->label_z->setText(QString::number(P.z));


    this->currentPoint->coord = P;

    ui->push_reproj->setEnabled(true);

    if(ui->checkBox_autoReproj->checkState() == Qt::Checked){
        this->reproj();
    }
}

void q3D2DDlg::reproj()
{
    //std::cout<<"Reprojection..."<<std::endl;

    //this->m_pickingHub->removeListener(this);
    std::vector<cc3D2DImage> images;
    images= this->currentWorkSite->images;

    std::vector<cc3D2DImage> selectedImgs;
    bool test = false;
    ui->listImg->clear();
    std::cout<<"Distorsion coefs"<<std::endl;
    std::cout<<images.at(0).calib.distorsionCoefs.x<<std::endl;
    std::cout<<images.at(0).calib.distorsionCoefs.y<<std::endl;
    std::cout<<images.at(0).calib.distorsionCoefs.z<<std::endl;

    std::cout<<"PPS"<<std::endl;
    std::cout<<images.at(1).calib.pps.x<<std::endl;
    std::cout<<images.at(1).calib.pps.y<<std::endl;

    std::cout<<"Focale"<<std::endl;
    std::cout<<images.at(2).calib.focale<<std::endl;

    ccPoint ptTest;
    CCVector3 coord;
    coord.x = 7.16786;
    coord.y = 2.85712;
    coord.z = -21.829;
    ptTest.coord = coord;



    for (int im = 0; im < images.size(); im++){
        std::cout<<"\n"<<std::endl;
        std::cout<<images.at(im).name.toStdString()<<std::endl;

        std::cout<<"Rotation"<<std::endl;
        std::cout<<images.at(im).ori.rotation.getValue(0,0)<<std::endl;
        std::cout<<images.at(im).ori.rotation.getValue(0,1)<<std::endl;
        std::cout<<images.at(im).ori.rotation.getValue(0,2)<<std::endl;

        std::cout<<images.at(im).ori.rotation.getValue(1,0)<<std::endl;
        std::cout<<images.at(im).ori.rotation.getValue(1,1)<<std::endl;
        std::cout<<images.at(im).ori.rotation.getValue(1,2)<<std::endl;

        std::cout<<images.at(im).ori.rotation.getValue(2,0)<<std::endl;
        std::cout<<images.at(im).ori.rotation.getValue(2,1)<<std::endl;
        std::cout<<images.at(im).ori.rotation.getValue(2,2)<<std::endl;

        std::cout<<"Sommet de prive de vue:"<<std::endl;
        std::cout<<images.at(im).ori.sommetPdV.x<<std::endl;
        std::cout<<images.at(im).ori.sommetPdV.y<<std::endl;
        std::cout<<images.at(im).ori.sommetPdV.z<<std::endl;


        //CCVector2 coordImg = images.at(im).formuleImg(*this->currentPoint);

        CCVector2 coordImg = images.at(im).formuleImg(ptTest);
        std::cout<<"Coord R du pt"<<std::endl;
//        std::cout<<this->currentPoint->coord.x<<std::endl;
//        std::cout<<this->currentPoint->coord.y<<std::endl;
//        std::cout<<this->currentPoint->coord.z<<std::endl;
        std::cout<<ptTest.coord.x<<std::endl;
        std::cout<<ptTest.coord.y<<std::endl;
        std::cout<<ptTest.coord.z<<std::endl;
        std::cout<< "Resultat formule image: "<<std::endl;
        std::cout<<coordImg.x<<coordImg.y<<std::endl;
        CCVector2 coordImgDisto = images.at(im).addDisto(coordImg);
        std::cout<< "Resultat +disto: "<<std::endl;
        std::cout<<coordImgDisto.x<<coordImgDisto.y<<std::endl;

        images.at(im).ptSelected = coordImgDisto;

        if (0 <= coordImgDisto.x && coordImgDisto.x<= images.at(im).calib.szIm.x){
            if ( 0 <= coordImgDisto.y && coordImgDisto.y<= images.at(im).calib.szIm.y){
                selectedImgs.push_back(images.at(im));
                std::cout<<"Img seleted"<<std::endl;
                QListWidgetItem *imgItem = new QListWidgetItem;
                imgItem->setText(images.at(im).name);
                ui->listImg->addItem(imgItem);
                test = true;
            }
        }
    }
    // Set the display button able only if there is some images to display.
    if (test){
        ui->push_display->setEnabled(true);
        this->currentWorkSite->selectedImgs = selectedImgs;
    }
}

void q3D2DDlg::displayImg()
{
    //std::cout<<"Displaying images..."<<std::endl;
    QList<QListWidgetItem*> selImgs;
    selImgs = ui->listImg->selectedItems();

    for (int im=0; im<selImgs.size(); im++){
        int rank = ui->listImg->row(selImgs.at(im));
        q3D2DDisplayImgDlg* dlgDispImg = new q3D2DDisplayImgDlg();
        dlgDispImg->dispImg(this->currentWorkSite->selectedImgs.at(rank));
        dlgDispImg->show();

    }
    //q3D2DDisplayImgDlg* dlgDispImg = new q3D2DDisplayImgDlg();
    //dlgDispImg->dispImgmoi(QPixmap("/home/prof/Documents/Iris/Fontaine/AIMG_2470.JPG"));
    //dlgDispImg->dispImgmoi(QPixmap("/home/iris/Documents/PPMD/ProjetInfo/Fontaine/AIMG_2470.JPG"));
    //dlgDispImg->show();

}

