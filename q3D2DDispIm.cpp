#include "q3D2DDispIm.h"

#include <iostream>

// Constructor of the class
q3D2DDispIm::q3D2DDispIm(QWidget *parent) :
    QMainWindow(parent)
{

    // Create a the image widget
    imgWidget = new rOg_image();

#ifdef LOAD_RAW_RGB_DATA

    // Prepare raw image data, format is RGBRGBRGB...
    data = new uchar [WIDTH*HEIGHT*3];
    int index=0;
    for (int y=0;y<HEIGHT;y++)
        for (int x=0;x<WIDTH;x++)
        {
            data[index++]=0xFF * (x<(2.*WIDTH/3.)); // || 0x00;
            data[index++]=0xFF * (x>(WIDTH/3.) && (x<(2*WIDTH/3.)));
            data[index++]=0xFF * (x>(WIDTH/3.));
        }
    // Draw the raw image in the image widget
    imgWidget->setImageFromRawData(data,WIDTH,HEIGHT);
#else
    std::cout<<"hey"<<std::endl;
    // Draw the Qt image in the image widget
    imgWidget->setImage(QImage("qt.jpg"));

#endif

    // Set background color (gray)
    imgWidget->setBackgroundBrush(QBrush(QColor(0x7F,0x7F,0x7F)));

    // Add the widget in the window
    setCentralWidget(imgWidget);
}




// Destructor of the class
q3D2DDispIm::~q3D2DDispIm()
{
    // Delete the widget
    delete imgWidget;


#ifdef LOAD_RAW_RGB_DATA
    // If a raw data image has been created, free memory
    delete data;
#endif
}
