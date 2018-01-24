#ifndef rOg_image_H
#define rOg_image_H

#include <QObject>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMenu>


// Default zoom factors
#define         DEFAULT_ZOOM_FACTOR             1.15
#define         DEFAULT_ZOOM_CTRL_FACTOR        1.01




/*!
 * \brief The rOg_image class       This class has been designed to display an image
 *                                  The image can be zoomed or moved with the mouse
 *                                  By overloading this class, it is possible to draw over the image (drawOnImage)
 *                                  or in the view port (drawInViewPort)
 */
class rOg_image : public QGraphicsView
{
    Q_OBJECT

public:


    /*!
     * \brief rOg_image             Constructor, create the scene and set parameters
     * \param isContextualMenu      When set to true, the contextual menu is initialize
     *                              If you don't want contextual menu or need to create a
     *                              custom one, set to false.
     */
    rOg_image( bool isContextualMenu=true, QWidget * parent=0);
    ~rOg_image();


    /*!
     * \brief setImage          Set the image in the widget
     * \param image             QImage to display
     */
    void                    setImage(const QImage & image);


    /*!
     * \brief setImageFromRawData   Set the image from raw data
     * \param data                  Pointer to the raw data (data format is RGBRGBRGBRGB ...)
     * \param size                  Size of the image to display
     * \note                        The raw data MUST be compliant with the size
     */
    void                    setImageFromRawData(const uchar * data, int width, int height,
                                                bool mirrorHorizontally=false, bool mirrorVertically=false);


    /*!
     * \brief setZoomFactor     Set the zoom factor when the CTRL key is not pressed
     * \param factor            zoom factor (>1)
     */
    void                    setZoomFactor(const double factor) { zoomFactor=factor; }


    /*!
     * \brief setZoomCtrlFactor     Set the zoom factor when the CTRL key is pressed
     * \param factor                zoom factor (>1)
     */
    void                    setZoomCtrlFactor(const double factor) {zoomCtrlFactor=factor; }




public slots:

    /*!
     * \brief fitImage              This function fit the image in the view while keeping aspect ratio
     */
    void                    fitImage();



protected:


    /*!
     * \brief drawOnImage           Overload this function to draw over the image
     * \param painter               Painter for drawing
     * \param imageSize             Size of the image
     */
    virtual void            drawOnImage(QPainter* painter, QSize imageSize);


    /*!
     * \brief drawOnImage           Overload this function to draw in the view port
     * \param painter               Painter for drawing
     * \param imageSize             Size of the view port
     */
    virtual void            drawInViewPort(QPainter* painter, QSize portSize);


    /*!
     * \brief drawForeground        Drawing he foreground of the scene
     *                              When overloading this function, you must call it parent before
     *                              exiting the function, otherwise drawOnImage and drawInViewPort
     *                              will not work properly
     * \param painter               Painter for drawing
     * \param rect                  The area of the scene displayed in the view port
     */
    virtual void            drawForeground(QPainter *painter, const QRectF &rect);


    /*!
     * \brief setToolTipText        Display the tool tip over the mouse
     * \param imageCoordinates      Coordinates of the mouse in the image's frame
     * \return                      The function returns the QString that is displayed over the image
     */
    virtual QString         setToolTipText(QPoint imageCoordinates);


    /*!
     * \brief mousePressEvent       Overload this function to process mouse button pressed
     * \param event                 mouse event
     */
    virtual void            mousePressEvent(QMouseEvent *event);


    /*!
     * \brief mouseReleaseEvent     Overload this function to process mouse button released
     * \param event                 mouse event
     */
    virtual void            mouseReleaseEvent(QMouseEvent *event);


    /*!
     * \brief wheelEvent            Overload this function to process mouse wheel event
     * \param event                 mouse wheel event
     */
    virtual void            wheelEvent(QWheelEvent *event);


    /*!
     * \brief mouseMoveEvent        Overload this function to process mouse moves
     * \param event                 mouse move event
     */
    virtual void            mouseMoveEvent(QMouseEvent *event);


    /*!
     * \brief resizeEvent        Overload this function to process the window resizing event
     * \param event              resize event
     */
    virtual void            resizeEvent(QResizeEvent *event);


protected slots:


    /*!
     * \brief showContextMenu       Display the contextual menu (on right click)
     * \param pos                   Position of the mouse in the widget
     */
    virtual void            showContextMenu(const QPoint & pos);


private:

    // Scene where the image is drawn
    QGraphicsScene*         scene;

    // Pixmap item containing the image
    QGraphicsPixmapItem*    pixmapItem;

    // Size of the current image
    QSize                   imageSize;

    // Zoom factor
    double                  zoomFactor;

    // Zoom factor when the CTRL key is pressed
    double                  zoomCtrlFactor;

    // Current pixmap
    QPixmap                 pixmap;


};

#endif // rOg_image_H
