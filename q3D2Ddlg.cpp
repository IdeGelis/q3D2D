//System
#include <iostream>
#include <string>

//3D2D
//#include "ccCalibration.h"
//#include "ccOrientation.h"
#include "ccWorkSite.h"
#include "q3D2Ddlg.h"
#include "ui_q3D2Ddlg.h"

//Qt
#include "qfiledialog.h"
#include <QString>
#include <QDir>

q3D2DDlg::q3D2DDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::q3D2DDlg)
{
    ui->setupUi(this);

    //Connexion of butons
    QObject::connect(ui->push_load,SIGNAL(released()),this,SLOT(load()));
    //QObject::connect(ui->push_loadImg,SIGNAL(released()),this,SLOT(loadImgFolder()));
    //QObject::connect(ui->push_params,SIGNAL(released()),this,SLOT(loadParamsFolder()));
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
    QString dirImg = QFileDialog::getExistingDirectory(this, tr("Select Images Directory"),
                                                               QDir::homePath(),
                                                               QFileDialog::ShowDirsOnly
                                                               | QFileDialog::DontResolveSymlinks);

    // Parameters folder is usually the same as images folder
    QDir parentDirImg  = QDir(dirImg);
    parentDirImg.cdUp();
    QString dirParam = QFileDialog::getExistingDirectory(this, tr("Select the folder containing parameters files"),
                                                         parentDirImg.absolutePath(),
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);



    //Creation of the work site
    //ccWorkSite currentWorkSite(dirImg,dirParam);

    //std::cout<<"creation current work site ok!"<<std::endl;
    //currentWorkSite.initialise();

}

//void q3D2DDlg::loadImgFolder()
//{
//    std::cout<<"Loading the folder containning images..."<<std::endl;
//    QString folderName = QFileDialog::getExistingDirectory(this, tr("Select Images Directory"),
//                                                           "/home",
//                                                           QFileDialog::ShowDirsOnly
//                                                           | QFileDialog::DontResolveSymlinks);


//}

//void q3D2DDlg::loadParamsFolder()
//{
//    std::cout<<"Loading the folder containning parameters files..."<<std::endl;
//}

void q3D2DDlg::selectPt()
{
    std::cout<<"Selecting mode"<<std::endl;
}

void q3D2DDlg::reproj()
{
    std::cout<<"Reprojection..."<<std::endl;
}

void q3D2DDlg::displayImg()
{
    std::cout<<"Displaying images..."<<std::endl;
}
