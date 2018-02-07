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
#include "math.h"

//3D2D
#include "ccWorkSite.h"
#include "q3D2Ddlg.h"
#include "ui_q3D2Ddlg.h"
#include "ccPoint.h"
#include "cc3D2DImage.h"
#include "q3D2DDisplayImgDlg.h"

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
#include "ccPointCloud.h"


q3D2DDlg::q3D2DDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::q3D2DDlg)
{
    ui->setupUi(this);

    this->currentWorkSite = new ccWorkSite();

    this->currentPoint = new ccPoint();

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
    QString dirImgStr = QFileDialog::getExistingDirectory(this, tr("Sélectionner le dossier contenant les images"),
                                                               QDir::homePath(),
                                                               QFileDialog::ShowDirsOnly
                                                               | QFileDialog::DontResolveSymlinks);

    // Parameters folder is usually the same as images folder
    QString dirParamStr = QFileDialog::getExistingDirectory(this, tr("Sélectionner le dossier contenant les fichiers XML d'orientation"),
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

    //Set to picking Mode
    this->m_pickingHub = this->m_app->pickingHub();
    this->m_pickingHub->addListener(this,true,true);

}

//This function is called when a point is picked (through the picking hub)
void q3D2DDlg::onItemPicked(const ccPickingListener::PickedItem& pi)
{
    CCVector3 normal = CCVector3(0,0,0);
    if (pi.entity->isKindOf(CC_TYPES::POINT_CLOUD)){
        //get point cloud
        ccPointCloud* cloud = static_cast<ccPointCloud*>(pi.entity); //cast to point cloud

        // Ceck if the point clouds has normal
        if (cloud->hasNormals()){
            //Get the normal
            normal = cloud->getPointNormal(pi.itemIndex);
        }
    }

    pointPicked(pi.entity, pi.itemIndex, pi.clickPoint.x(), pi.clickPoint.y(), pi.P3D, normal); //map straight to pointPicked function
}

//Process point picks
void q3D2DDlg::pointPicked(ccHObject* entity, unsigned itemIdx, int x, int y, const CCVector3& P, CCVector3 N)
{
    if (!entity) //null pick
    {
        return;
    }

    ui->label_x->setText(QString::number(P.x));
    ui->label_y->setText(QString::number(P.y));
    ui->label_z->setText(QString::number(P.z));


    this->currentPoint->coord = P;
    this->currentPoint->normal = N;
    this->currentPoint->normal.normalize();

    ui->push_reproj->setEnabled(true);




    if(ui->checkBox_autoReproj->checkState() == Qt::Checked){
        this->reproj();
    }
}

void q3D2DDlg::reproj()
{
    //std::cout<<"Reprojection..."<<std::endl;
    //Si on n'est pas en mode reprojection automatique il faut désactiver le mode sélection de point
    if(ui->checkBox_autoReproj->checkState() != Qt::Checked){
        //Set picking mode off
        this->m_pickingHub->removeListener(this);
    }

    std::vector<cc3D2DImage> images;
    images= this->currentWorkSite->images;

    std::vector<cc3D2DImage> selectedImgs;
    bool test = false;
    ui->listImg->clear();

    //List containing all the agles between normal et shooting vector
    //It will be used if the case show the best image is checked
    std::vector<double> angles;

    for (int im = 0; im < images.size(); im++){
        std::cout<<images.at(im).name.toStdString()<<std::endl;

        //Test for hidden parts
        //si le nuage n'a pas de normal alors le produit scalaire avec un vecteur nul done un angle de PI/2 donc toutes les images passent ce test
        double angleNormVecVis = acos(images.at(im).vectVisee.dot(this->currentPoint->normal));
        angles.push_back(angleNormVecVis);
        std::cout<<angleNormVecVis<<std::endl;

        if (angleNormVecVis>=M_PI/2){
            CCVector2 coordImg = images.at(im).formuleImg(*this->currentPoint);
            CCVector2 coordImgDisto = images.at(im).addDisto(coordImg);

            images.at(im).ptSelected = coordImgDisto;

            if (0 <= coordImgDisto.x && coordImgDisto.x<= images.at(im).calib.szIm.x){
                if ( 0 <= coordImgDisto.y && coordImgDisto.y<= images.at(im).calib.szIm.y){
                    selectedImgs.push_back(images.at(im));
                    //std::cout<<"Img seleted"<<std::endl;
                    QListWidgetItem *imgItem = new QListWidgetItem;
                    imgItem->setText(images.at(im).name);
                    ui->listImg->addItem(imgItem);
                    test = true;
                }
            }
        }
    }
    // Set the display button able only if there is some images to display.
    if (test){
        ui->push_display->setEnabled(true);
        this->currentWorkSite->selectedImgs = selectedImgs;
    }

    if (ui->checkBox_BestImg->checkState() == Qt::Checked){
        //Get the range of the maximum angle between the normal of the point and the shooting vector
        int rangeMaxElt = std::distance(angles.begin(),std::max_element(angles.begin(),angles.end()));

        //std::cout<<std::max_element(angles.begin(),angles.end())<<std::endl;
        q3D2DDisplayImgDlg* dlgDispImg = new q3D2DDisplayImgDlg();
        dlgDispImg->dispImg(images.at(rangeMaxElt));
        dlgDispImg->show();

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
}

