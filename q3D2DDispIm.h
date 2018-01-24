#ifndef Q3D2DDISPIM_H
#define Q3D2DDISPIM_H

#include <QMainWindow>
#include <QTimer>
#include <rOg_image.h>


#define WIDTH 600
#define HEIGHT 400
//#define LOAD_RAW_RGB_DATA

/*!
 * \brief The q3D2DDispIm class      Create the mainwindow and add the widget inside
 */
class q3D2DDispIm : public QMainWindow
{
    Q_OBJECT

public:

    /*!
     * \brief q3D2DDispIm            Class constructor
     * \param parent
     */
    explicit                        q3D2DDispIm(QWidget *parent = 0);
    ~q3D2DDispIm();



private:
    uchar*      data;

    QTimer*     mainTimer;

    // Widget containing the image
    rOg_image*                      imgWidget;

};

#endif // Q3D2DDISPIM_H

