#ifndef Q3D2DDISPLAYIMGDLG_H
#define Q3D2DDISPLAYIMGDLG_H

//Qt
#include <QDialog>
#include <QGraphicsScene>

//3D2D
#include "cc3D2DImage.h"

namespace Ui {
class q3D2DDisplayImgDlg;
}

class q3D2DDisplayImgDlg : public QDialog
{
    Q_OBJECT

public:
    explicit q3D2DDisplayImgDlg(QWidget *parent = 0);
    ~q3D2DDisplayImgDlg();
    void dispImg(cc3D2DImage img);

private:
    Ui::q3D2DDisplayImgDlg *ui;
    QGraphicsScene mScene;
};

#endif // Q3D2DDISPLAYIMGDLG_H
