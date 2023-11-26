#include "BitmapIcon.h"


GLbitmap::GLbitmap()
{

	x = 0;
	y = 0;


};

GLbitmap::~GLbitmap()
{

};

int GLbitmap::initial(QString filename, int px, int py)
{
    (*this).iconImage.load(filename);

    // Check if the image is valid
    if ((*this).iconImage.isNull()) {
        qDebug() << "Failed to load the icon.";
        return -1;
    }

    (*this).iconImage.mirror(false,true);

    (*this).x = px;
    (*this).y = py;

    return 0;



};


/*
unsigned char* databitmap;


	QBitmap BitContext;

*/