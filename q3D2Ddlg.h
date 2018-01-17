#ifndef Q3D2DDLG_H
#define Q3D2DDLG_H

//Qt
#include <QDialog>

//3D2D
#include "ccWorkSite.h"

namespace Ui {
class q3D2DDlg;
}

class q3D2DDlg : public QDialog
{
    Q_OBJECT

public:
    explicit q3D2DDlg(QWidget *parent = 0);
    ~q3D2DDlg();

private:
    Ui::q3D2DDlg *ui;
    ccWorkSite *currentWorkSite;

public slots:
    //void loadImgFolder();
    //void loadParamsFolder();
    void load();
    void reproj();
    void displayImg();
    void selectPt();

};

#endif // Q3D2DDLG_H
