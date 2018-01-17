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

//3D2D
#include "ccWorkSite.h"
#include "q3D2Ddlg.h"
#include "ui_q3D2Ddlg.h"

//Qt
#include "qfiledialog.h"
#include <QString>
#include <QDir>
#include <QXmlStreamReader>

//qCC
#include <ccGLWindow.h>

q3D2DDlg::q3D2DDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::q3D2DDlg)
{
    ui->setupUi(this);
//    ccWorkSite currentWorkSite();
//    ccWorkSite *ptrCurrentWS(0);
//    ptrCurrentWS= &currentWorkSite;
    this->currentWorkSite = new ccWorkSite();
    //ccWorkSite *currentWorkSite(0);
    //currentWorkSite = new ccWorkSite;
    std::cout<<currentWorkSite->pathFolderImg.toStdString()<<std::endl;
    //std::cout<<ptrCurrentWS<<std::endl;
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
//    QString dirImgStr = QFileDialog::getExistingDirectory(this, tr("Select Images Directory"),
//                                                          QString("~/Documents/PPMD/ProjetInfo"),
//                                                          QFileDialog::ShowDirsOnly
//                                                          | QFileDialog::DontResolveSymlinks);
    // Parameters folder is usually the same as images folder
    QString dirParamStr = QFileDialog::getExistingDirectory(this, tr("Select the folder containing parameters files"),
                                                         QDir(dirImgStr).absolutePath(),
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);



    //Creation of the work site
    //ccWorkSite currentWorkSite(dirImgStr,dirParamStr);
    std::cout<<"creation current work site ok!"<<std::endl;
    this->currentWorkSite->initialise(dirImgStr,dirParamStr);
    ui->label_img->setText(dirImgStr);
    ui->label_param->setText(dirParamStr);
    ui->push_slctPt->setEnabled(true);


}


void q3D2DDlg::selectPt()
{
    std::cout<<"Selecting mode"<<std::endl;
    //http://www.cloudcompare.org/forum/viewtopic.php?t=514

//    ccGLWindow* win = m_app->getActiveGLWindow();
//    if (win)
//        win->setPickingMode(POINT_PICKING);
}

void q3D2DDlg::reproj()
{
    std::cout<<"Reprojection..."<<std::endl;
}

void q3D2DDlg::displayImg()
{
    std::cout<<"Displaying images..."<<std::endl;
}
