
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
void q3D2DDisplayImgDlg::dispImgmoi(QPixmap img)
{
    mScene.clear();
    mScene.addPixmap(img);
}

//void q3D2DDisplayImgDlg::dispImgmoi(QPixmap img)
//{
//    //mScene.clear();
//    // Allow mouse tracking even if no button is pressed
//    ui->graphicsView->setMouseTracking(true);

//    // Add the scene to the QGraphicsView
//    //ui->graphicsView->setScene(scene);

//    // Update all the view port when needed, otherwise, the drawInViewPort may experience trouble
//    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

//    // When zooming, the view stay centered over the mouse
//    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

//    ui->graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);

//    // Initialize contextual menu if requested
////    if (isContextualMenu)
////    {
////        setContextMenuPolicy(Qt::CustomContextMenu);
////        connect(ui->graphicsView, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
////    }

//    // Disable scroll bar to avoid a unwanted resize recursion
//    //    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    //    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//    mScene.addPixmap(img);
//}

//// Display contextual menu
//void q3D2DDisplayImgDlg::showContextMenu(const QPoint & pos)
//{
//    // Get the mouse position in the scene
//    QPoint globalPos = mapToGlobal(pos);
//    // Create the menu and add action
//    QMenu contextMenu;
//    contextMenu.addAction("Reset view", this, SLOT(fitImage()));
//    // Display the menu
//    contextMenu.exec(globalPos);
//}




//// Set or update the image in the scene
//void q3D2DDisplayImgDlg::setImage(const QImage & image)
//{
//    // Update the pixmap in the scene
//    pixmap=QPixmap::fromImage(image);
//    pixmapItem->setPixmap(pixmap);

//    // Resize the scene (needed is the new image is smaller)
//    scene->setSceneRect(QRect (QPoint(0,0),image.size()));
//    std::cout<<"setImahe"<<std::endl;
//    // Store the image size
//    imageSize = image.size();
//}


//// Set an image from raw data
//void q3D2DDisplayImgDlg::setImageFromRawData(const uchar * data, int width, int height, bool mirrorHorizontally, bool mirrorVertically)
//{
//    // Convert data into QImage
//    QImage image(data, width, height, width*3, QImage::Format_RGB888);

//    // Update the pixmap in the scene
//    pixmap=QPixmap::fromImage(image.mirrored(mirrorHorizontally,mirrorVertically));
//    pixmapItem->setPixmap(pixmap);

//    // Resize the scene (needed is the new image is smaller)
//    scene->setSceneRect(QRect (QPoint(0,0),image.size()));

//    // Store the image size
//    imageSize = image.size();
//}



//// Fit the image in the widget
//void q3D2DDisplayImgDlg::fitImage()
//{
//    // Get current scroll bar policy
//    Qt::ScrollBarPolicy	currentHorizontalPolicy = horizontalScrollBarPolicy();
//    Qt::ScrollBarPolicy	currentverticalPolicy = verticalScrollBarPolicy();

//    // Disable scroll bar to avoid a margin around the image
//    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//    // Fit the scene in the QGraphicsView
//    this->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

//    // Restaure scroll bar policy
//    setHorizontalScrollBarPolicy(currentHorizontalPolicy);
//    setVerticalScrollBarPolicy(currentverticalPolicy);
//}


//// Called when a mouse button is pressed
//void q3D2DDisplayImgDlg::mousePressEvent(QMouseEvent *event)
//{
//    // Drag mode : change the cursor's shape
//    if (event->button() == Qt::LeftButton)  this->setDragMode(QGraphicsView::ScrollHandDrag);
//    //    if (event->button() == Qt::RightButton) this->fitImage();
//    QGraphicsView::mousePressEvent(event);
//}


//// Called when a mouse button is pressed
//void q3D2DDisplayImgDlg::mouseReleaseEvent(QMouseEvent *event)
//{
//    // Exit drag mode : change the cursor's shape
//    if (event->button() == Qt::LeftButton) this->setDragMode(QGraphicsView::NoDrag);
//    QGraphicsView::mouseReleaseEvent(event);
//}


//#ifndef QT_NO_WHEELEVENT

//// Call when there is a scroll event (zoom in or zoom out)
//void q3D2DDisplayImgDlg::wheelEvent(QWheelEvent *event)
//{
//    // When zooming, the view stay centered over the mouse
//    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

//    double factor = (event->modifiers() & Qt::ControlModifier) ? zoomCtrlFactor : zoomFactor;
//    if(event->delta() > 0)
//        // Zoom in
//        scale(factor, factor);
//    else
//        // Zooming out
//        scale(1.0 / factor, 1.0 / factor);

//    // The event is processed
//    event->accept();
//}

//#endif


//// Overload the mouse MoveEvent to display the tool tip
//void q3D2DDisplayImgDlg::mouseMoveEvent(QMouseEvent *event)
//{
//    // Get the coordinates of the mouse in the scene
//    QPointF imagePoint = mapToScene(QPoint(event->x(), event->y() ));
//    // Call the function that create the tool tip
//    setToolTip(setToolTipText(QPoint((int)imagePoint.x(),(int)imagePoint.y())));
//    // Call the parent's function (for dragging)
//    QGraphicsView::mouseMoveEvent(event);
//}


//// Overload the function to draw over the image
//void q3D2DDisplayImgDlg::drawForeground(QPainter *painter, const QRectF&)
//{

//    // Call the function to draw over the image
//    this->drawOnImage(painter,imageSize);

//    // Reset transformation and call the function draw in the view port
//    painter->resetTransform();

//    // Call the function to draw in the view port
//    this->drawInViewPort(painter, this->viewport()->size());
//}


//// Overloaded functionthat catch the resize event
//void q3D2DDisplayImgDlg::resizeEvent(QResizeEvent *event)
//{
//    // First call, the scene is created
//    if(event->oldSize().width() == -1 || event->oldSize().height() == -1) return;

//    // Get the previous rectangle of the scene in the viewport
//    QPointF P1=mapToScene(QPoint(0,0));
//    QPointF P2=mapToScene(QPoint(event->oldSize().width(),event->oldSize().height()));

//    // Stretch the rectangle around the scene
//    if (P1.x()<0) P1.setX(0);
//    if (P1.y()<0) P1.setY(0);
//    if (P2.x()>scene->width()) P2.setX(scene->width());
//    if (P2.y()>scene->height()) P2.setY(scene->height());

//    // Fit the previous area in the scene
//    this->fitInView(QRect(P1.toPoint(),P2.toPoint()),Qt::KeepAspectRatio);
//}





//// Define the virtual function to avoid the "unused parameter" warning
//QString q3D2DDisplayImgDlg::setToolTipText(QPoint imageCoordinates)
//{
//    (void)imageCoordinates;
//    return QString("");
//}


//// Define the virtual function to avoid the "unused parameter" warning
//void q3D2DDisplayImgDlg::drawOnImage(QPainter* , QSize )
//{}


//// Define the virtual function to avoid the "unused parameter" warning
//void q3D2DDisplayImgDlg::drawInViewPort(QPainter* , QSize )
//{}


