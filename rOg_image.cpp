#include "rOg_image.h"
#include <QGraphicsScene>

#include <iostream>
// Constructor of the class, create the scene and set default parameters
rOg_image::rOg_image(bool isContextualMenu, QWidget * parent) :
    QGraphicsView(parent)
{
    // Set default zoom factors
    zoomFactor=DEFAULT_ZOOM_FACTOR;
    zoomCtrlFactor=DEFAULT_ZOOM_CTRL_FACTOR;

    // Create the scene
    scene = new QGraphicsScene();

    // Allow mouse tracking even if no button is pressed
    this->setMouseTracking(true);

    // Add the scene to the QGraphicsView
    this->setScene(scene);

    // Update all the view port when needed, otherwise, the drawInViewPort may experience trouble
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    // When zooming, the view stay centered over the mouse
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    this->setResizeAnchor(QGraphicsView::AnchorViewCenter);

    // Initialize contextual menu if requested
    if (isContextualMenu)
    {
        setContextMenuPolicy(Qt::CustomContextMenu);
        connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
    }

    // Disable scroll bar to avoid a unwanted resize recursion
//    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Add the default pixmap at startup
    pixmapItem = scene->addPixmap(pixmap);

}


// Destructor of the class
rOg_image::~rOg_image()
{
    delete pixmapItem;
    delete scene;
}



// Display contextual menu
void rOg_image::showContextMenu(const QPoint & pos)
{
    // Get the mouse position in the scene
    QPoint globalPos = mapToGlobal(pos);
    // Create the menu and add action
    QMenu contextMenu;
    contextMenu.addAction("Reset view", this, SLOT(fitImage()));
    // Display the menu
    contextMenu.exec(globalPos);
}




// Set or update the image in the scene
void rOg_image::setImage(const QImage & image)
{
    // Update the pixmap in the scene
    pixmap=QPixmap::fromImage(image);
    pixmapItem->setPixmap(pixmap);

    // Resize the scene (needed is the new image is smaller)
    scene->setSceneRect(QRect (QPoint(0,0),image.size()));
    std::cout<<"setImahe"<<std::endl;
    // Store the image size
    imageSize = image.size();
}


// Set an image from raw data
void rOg_image::setImageFromRawData(const uchar * data, int width, int height, bool mirrorHorizontally, bool mirrorVertically)
{
    // Convert data into QImage
    QImage image(data, width, height, width*3, QImage::Format_RGB888);

    // Update the pixmap in the scene
    pixmap=QPixmap::fromImage(image.mirrored(mirrorHorizontally,mirrorVertically));
    pixmapItem->setPixmap(pixmap);

    // Resize the scene (needed is the new image is smaller)
    scene->setSceneRect(QRect (QPoint(0,0),image.size()));

    // Store the image size
    imageSize = image.size();
}



// Fit the image in the widget
void rOg_image::fitImage()
{
    // Get current scroll bar policy
    Qt::ScrollBarPolicy	currentHorizontalPolicy = horizontalScrollBarPolicy();
    Qt::ScrollBarPolicy	currentverticalPolicy = verticalScrollBarPolicy();

    // Disable scroll bar to avoid a margin around the image
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Fit the scene in the QGraphicsView
    this->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    // Restaure scroll bar policy
    setHorizontalScrollBarPolicy(currentHorizontalPolicy);
    setVerticalScrollBarPolicy(currentverticalPolicy);
}


// Called when a mouse button is pressed
void rOg_image::mousePressEvent(QMouseEvent *event)
{
    // Drag mode : change the cursor's shape
    if (event->button() == Qt::LeftButton)  this->setDragMode(QGraphicsView::ScrollHandDrag);
    //    if (event->button() == Qt::RightButton) this->fitImage();
    QGraphicsView::mousePressEvent(event);
}


// Called when a mouse button is pressed
void rOg_image::mouseReleaseEvent(QMouseEvent *event)
{
    // Exit drag mode : change the cursor's shape
    if (event->button() == Qt::LeftButton) this->setDragMode(QGraphicsView::NoDrag);
    QGraphicsView::mouseReleaseEvent(event);
}


#ifndef QT_NO_WHEELEVENT

// Call when there is a scroll event (zoom in or zoom out)
void rOg_image::wheelEvent(QWheelEvent *event)
{
    // When zooming, the view stay centered over the mouse
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    double factor = (event->modifiers() & Qt::ControlModifier) ? zoomCtrlFactor : zoomFactor;
    if(event->delta() > 0)
        // Zoom in
        scale(factor, factor);
    else
        // Zooming out
        scale(1.0 / factor, 1.0 / factor);

    // The event is processed
    event->accept();
}

#endif


// Overload the mouse MoveEvent to display the tool tip
void rOg_image::mouseMoveEvent(QMouseEvent *event)
{
    // Get the coordinates of the mouse in the scene
    QPointF imagePoint = mapToScene(QPoint(event->x(), event->y() ));
    // Call the function that create the tool tip
    setToolTip(setToolTipText(QPoint((int)imagePoint.x(),(int)imagePoint.y())));
    // Call the parent's function (for dragging)
    QGraphicsView::mouseMoveEvent(event);
}


// Overload the function to draw over the image
void rOg_image::drawForeground(QPainter *painter, const QRectF&)
{

    // Call the function to draw over the image
    this->drawOnImage(painter,imageSize);

    // Reset transformation and call the function draw in the view port
    painter->resetTransform();

    // Call the function to draw in the view port
    this->drawInViewPort(painter, this->viewport()->size());
}


// Overloaded functionthat catch the resize event
void rOg_image::resizeEvent(QResizeEvent *event)
{
    // First call, the scene is created
    if(event->oldSize().width() == -1 || event->oldSize().height() == -1) return;

    // Get the previous rectangle of the scene in the viewport
    QPointF P1=mapToScene(QPoint(0,0));
    QPointF P2=mapToScene(QPoint(event->oldSize().width(),event->oldSize().height()));

    // Stretch the rectangle around the scene
    if (P1.x()<0) P1.setX(0);
    if (P1.y()<0) P1.setY(0);
    if (P2.x()>scene->width()) P2.setX(scene->width());
    if (P2.y()>scene->height()) P2.setY(scene->height());

    // Fit the previous area in the scene
    this->fitInView(QRect(P1.toPoint(),P2.toPoint()),Qt::KeepAspectRatio);
}





// Define the virtual function to avoid the "unused parameter" warning
QString rOg_image::setToolTipText(QPoint imageCoordinates)
{
    (void)imageCoordinates;
    return QString("");
}


// Define the virtual function to avoid the "unused parameter" warning
void rOg_image::drawOnImage(QPainter* , QSize )
{}


// Define the virtual function to avoid the "unused parameter" warning
void rOg_image::drawInViewPort(QPainter* , QSize )
{}

