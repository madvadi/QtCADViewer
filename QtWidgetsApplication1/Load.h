#pragma once
#ifndef _LOAD_H_ 
#define _LOAD_H_

#include <iostream>
#include <cstdio>
#include <vector>

#include "qopengl.h"
#include <qopenglwidget.h>
#include <qopenglfunctions.h>→



#include "RenderAssist.h"
//#include <math>


using namespace std;

class loadSTL
{
public:

	loadSTL();
	~loadSTL();


	void loadBIN(const char* filename);


	void loadASCII(const char* filename);

	void render(vector<RenderAssist>& RA_ptr);

	std::vector<float> xyz;

private:

	//uint8_t  sizeheader[10];
	uint32_t Ntrig;

	int tri_num;

	int header_size;

	char* cptr;

	float* xyz_f;



};

#endif

