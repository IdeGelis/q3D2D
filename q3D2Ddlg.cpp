#include "q3D2Ddlg.h"
#include "ui_q3D2Ddlg.h"

q3D2DDlg::q3D2DDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::q3D2DDlg)
{
    ui->setupUi(this);
}

q3D2DDlg::~q3D2DDlg()
{
    delete ui;
}
