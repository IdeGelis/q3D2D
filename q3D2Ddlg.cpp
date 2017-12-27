
//System
#include <iostream>

//3D2D
#include "ccCalibration.h"
//#include "ccOrientation.h"
#include "q3D2Ddlg.h"
#include "ui_q3D2Ddlg.h"


//Qt
#include "qfiledialog.h"
#include <QString>

q3D2DDlg::q3D2DDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::q3D2DDlg)
{
    ui->setupUi(this);

    //Connexion of butons
    QObject::connect(ui->push_loadImg,SIGNAL(released()),this,SLOT(loadImgFolder()));
    QObject::connect(ui->push_params,SIGNAL(released()),this,SLOT(loadParamsFolder()));
    QObject::connect(ui->push_slctPt,SIGNAL(released()),this,SLOT(selectPt()));
    QObject::connect(ui->push_reproj,SIGNAL(released()),this,SLOT(reproj()));
    QObject::connect(ui->push_display,SIGNAL(released()),this,SLOT(displayImg()));

}

q3D2DDlg::~q3D2DDlg()
{
    delete ui;
}

void q3D2DDlg::loadImgFolder()
{
    std::cout<<"Loading the folder containning images..."<<std::endl;
    QString folderName = QFileDialog::getOpenFileName(this,tr("Choix du dossier contenant les images"),"/",tr("Image (*.png *.xpm *.jpg)"));
    //QString fol = QFileDialog::getOpenFileName()
}

void q3D2DDlg::loadParamsFolder()
{
    std::cout<<"Loading the folder containning parameters files..."<<std::endl;
}

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
