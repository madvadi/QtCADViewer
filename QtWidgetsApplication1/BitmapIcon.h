#pragma once

#include <qdebug.h>
#include <qbitmap>


class GLbitmap
{
public:
	GLbitmap();

	~GLbitmap();

	int initial(QString filename, int x, int y);

	//unsigned char* databitmap;

	QImage iconImage;

	int x, y;

	//int height, width;

private:

	QBitmap BitContext;

};