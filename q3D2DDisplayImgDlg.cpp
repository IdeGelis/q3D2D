//System
#include <math.h>
#include <typeinfo>

//Qt
#include <QPainter>
#include <QRectF>
//3D2D
#include "q3D2DDisplayImgDlg.h"
#include "ui_q3D2DDisplayImgDlg.h"
#include "cc3D2DImage.h"

q3D2DDisplayImgDlg::q3D2DDisplayImgDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::q3D2DDisplayImgDlg)
{
    // Set default zoom factors
    zoomFactor=DEFAULT_ZOOM_FACTOR;
    zoomCtrlFactor=DEFAULT_ZOOM_CTRL_FACTOR;

    ui->setupUi(this);
    ui->graphicsView->setScene(&mScene);
    QObject::connect(ui->zoom_in,SIGNAL(released()),this,SLOT(zoom_in()));
    QObject::connect(ui->zoom_out,SIGNAL(released()),this,SLOT(zoom_out()));


//    ui->graphicsView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
//    ui->graphicsView->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );

}

q3D2DDisplayImgDlg::~q3D2DDisplayImgDlg()
{
    delete ui;
}


void q3D2DDisplayImgDlg::dispImg(cc3D2DImage img)
{

    ui->graphicsView->setBackgroundBrush(QBrush(QColor(0x7F,0x7F,0x7F)));
    this->setWindowTitle(img.name);

    mScene.addPixmap(img);
    QGraphicsItem *item;
    QRectF rect(10.0,10.0,10.0,10.0);
    QPen pen;
    pen.setWidth(3);
    pen.setBrush(QColor(156,0,0));
    pen.setJoinStyle(Qt::RoundJoin);
    item = mScene.addRect(rect,pen);

    // Change the position of the marker
    item->setPos(img.ptSelected.x-5.0,img.ptSelected.y-5.0);
    ui->graphicsView->centerOn(img.ptSelected.x,img.ptSelected.y);

}


#ifndef QT_NO_WHEELEVENT

// Call when there is a scroll event (zoom in or zoom out)
void q3D2DDisplayImgDlg::wheelEvent(QWheelEvent *event)
{
    // When zooming, the view stay centered over the mouse
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    double factor = (event->modifiers() & Qt::ControlModifier) ? zoomCtrlFactor : zoomFactor;
    if(event->delta() > 0)
        // Zoom in
        ui->graphicsView->scale(factor, factor);
    else
        // Zooming out
        ui->graphicsView->scale(1.0 / factor, 1.0 / factor);

    // The event is processed
    event->accept();
}

#endif
// Called when a mouse button is pressed
void q3D2DDisplayImgDlg::mousePressEvent(QMouseEvent *event)
{
    // Drag mode : change the cursor's shape
    if (event->button() == Qt::LeftButton){
        ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    }
    //    if (event->button() == Qt::RightButton) this->fitImage();
    //QGraphicsView::mousePressEvent(event);
}


// Called when a mouse button is pressed
void q3D2DDisplayImgDlg::mouseReleaseEvent(QMouseEvent *event)
{
    // Exit drag mode : change the cursor's shape
    if (event->button() == Qt::LeftButton){
        ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    }
    //QGraphicsView::mouseReleaseEvent(event);
}

void q3D2DDisplayImgDlg::zoom_in()
{
    ui->graphicsView->scale(this->zoomFactor, this->zoomFactor);
}

void q3D2DDisplayImgDlg::zoom_out()
{
   ui->graphicsView->scale(1.0/this->zoomFactor, 1.0/this->zoomFactor);
}


