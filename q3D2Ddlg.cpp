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
#include "ccPickingHub.h"
#include "ccMainAppInterface.h"


q3D2DDlg::q3D2DDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::q3D2DDlg)
{
    ui->setupUi(this);

    this->currentWorkSite = new ccWorkSite();

    // //!\\ Juste pour les tests à enlever dans la version finale
    ui->push_slctPt->setEnabled(true);

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
    //std::cout<<typeid(this->app).name()<<std::endl;
    ccPickingHub* m_pickingHub = this->app->pickingHub();
    m_pickingHub->togglePickingMode(true);
    //m_pickingHub->addListener();
    //connect(win, SIGNAL(itemPicked(ccHObject*, unsigned, int, int, const CCVector3&)), this, SLOT(processPickedPoint(ccHObject*, unsigned, int, int, const CCVector3&)));
//    this->startPicking();
//    this->win->setPickingMode(ccGLWindow::POINT_PICKING);
//    std::cout<<this->win->getPickingMode()<<std::endl;
//    this->win->setPickingMode(ccGLWindow::DEFAULT_PICKING);
//    std::cout<<this->win->getPickingMode()<<std::endl;
}

void q3D2DDlg::reproj()
{
    std::cout<<"Reprojection..."<<std::endl;
}

void q3D2DDlg::displayImg()
{
    std::cout<<"Displaying images..."<<std::endl;
}


//registers this plugin with the picking hub
//bool q3D2DDlg::startPicking()
//{
//    if (m_picking) //already picking... don't need to add again
//        return true;

//    //activate "point picking mode"
//    if (!m_app->pickingHub())  //no valid picking hub
//    {
//        m_app->dispToConsole("[q3D2D] Could not retrieve valid picking hub. Measurement aborted.", ccMainAppInterface::ERR_CONSOLE_MESSAGE);
//        return false;
//    }

//    if (!m_app->pickingHub()->addListener(this, true, true))
//    {
//        m_app->dispToConsole("Another tool is already using the picking mechanism. Stop it first", ccMainAppInterface::ERR_CONSOLE_MESSAGE);
//        return false;
//    }

//    m_picking = true;
//    return true;
//}
