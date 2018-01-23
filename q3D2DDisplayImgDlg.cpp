
//3D2D
#include "q3D2DDisplayImgDlg.h"
#include "ui_q3D2DDisplayImgDlg.h"
#include "cc3D2DImage.h"

q3D2DDisplayImgDlg::q3D2DDisplayImgDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::q3D2DDisplayImgDlg)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&mScene);
}

q3D2DDisplayImgDlg::~q3D2DDisplayImgDlg()
{
    delete ui;
}


void q3D2DDisplayImgDlg::dispImg(cc3D2DImage img)
{
    mScene.clear();
    mScene.addPixmap(QPixmap(img));
}
