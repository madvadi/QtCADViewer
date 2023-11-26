#pragma once
#ifndef _RENDERASSIST_H_
#define _RENDERASSIST_H_


class RenderAssist
{
public:
	RenderAssist();
	RenderAssist(RenderAssist* second);

	bool get_centre(float x, float y, float z);
	bool isPointInsideTriangle3D(float x, float y, float z);

	float dotProduct( float v1[3],  float v2[3]);

	// Function to subtract two vectors
	float* subtractVectors( float v1[3],  float v2[3]);

	float dotProduct2D(float v1[3], float v2[3]);

	// Function to subtract two vectors
	float* subtractVectors2D(float v1[3], float v2[3]);

	bool isPointInsideTriangle2D(float x, float y, float z);


	~RenderAssist();


	// Triangle infromation.
	float x[3][3];

};


#endif
