#ifndef Q3D2DDISPLAYIMGDLG_H
#define Q3D2DDISPLAYIMGDLG_H

//Qt
#include <QDialog>
#include <QGraphicsScene>
#include <QImage>
#include <QObject>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMenu>

//3D2D
#include "cc3D2DImage.h"

//system
#include <iostream>


// Default zoom factors
#define         DEFAULT_ZOOM_FACTOR             1.15
#define         DEFAULT_ZOOM_CTRL_FACTOR        1.01


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
    // Zoom factor
    double zoomFactor;
    // Zoom factor when the CTRL key is pressed
    double zoomCtrlFactor;

private slots:
    void zoom_out();
    void zoom_in();
    //void markerOff(cc3D2DImage img);

protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

};


#endif // Q3D2DDISPLAYIMGDLG_H
