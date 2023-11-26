#include "RenderAssist.h"



RenderAssist::RenderAssist()
{

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			x[i][j] = 0.0f;
		}
	}

};


RenderAssist::RenderAssist(RenderAssist* second)
{

	if (second == nullptr)
		return;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			x[i][j] = (*second).x[i][j];
		}
	}
};


bool RenderAssist::get_centre(float x, float y, float z)
{
	for (int i =0 ; i < 3; i++)
	{
		if (x == (*this).x[i][0] 
			&& y == (*this).x[i][1])
		{
			return true;

		}

	}


	return false;
};

// Function to calculate dot product of two vectors
float RenderAssist::dotProduct(float v1[3], float v2[3]) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
};

// Function to subtract two vectors
float* RenderAssist::subtractVectors(float v1[3], float v2[3]) {

	float temp[3] = {v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]};

	return temp;
};


float RenderAssist::dotProduct2D(float v1[3], float v2[3]) {
	return v1[0] * v2[0] + v1[1] * v2[1] ;
};

// Function to subtract two vectors
float* RenderAssist::subtractVectors2D(float v1[3], float v2[3]) {

	float temp[3] = { v1[0] - v2[0], v1[1] - v2[1]};

	return temp;
};

bool RenderAssist::isPointInsideTriangle2D(float x, float y, float z) {
	// Calculate vectors
	float* u = subtractVectors2D((*this).x[1], (*this).x[0]);
	float* v = subtractVectors2D((*this).x[2], (*this).x[0]);
	float vec[3] = { x,y,z };
	float* w = subtractVectors2D(vec, (*this).x[0]);

	// Calculate dot products
	float uu = dotProduct(u, u);
	float uv = dotProduct(u, v);
	float vv = dotProduct(v, v);
	float uw = dotProduct(u, w);
	float vw = dotProduct(v, w);

	// Calculate barycentric coordinates
	float denom = uv * uv - uu * vv;
	float u_bary = (uv * vw - vv * uw) / denom;
	float v_bary = (uv * uw - uu * vw) / denom;

	// Check if the point is inside the triangle
	return (u_bary >= 0 && v_bary >= 0 && (u_bary + v_bary) <= 1);

}; 

bool RenderAssist::isPointInsideTriangle3D(float x, float y, float z) {
	// Calculate vectors
	float* u = subtractVectors((*this).x[1], (*this).x[0]);
	float* v = subtractVectors((*this).x[2], (*this).x[0]);
	float vec[3] = { x,y,z };
	float* w = subtractVectors(vec, (*this).x[0]);

	// Calculate dot products
	float uu = dotProduct(u, u);
	float uv = dotProduct(u, v);
	float vv = dotProduct(v, v);
	float uw = dotProduct(u, w);
	float vw = dotProduct(v, w);

	// Calculate barycentric coordinates
	float denom = uv * uv - uu * vv;
	float u_bary = (uv * vw - vv * uw) / denom;
	float v_bary = (uv * uw - uu * vw) / denom;

	// Check if the point is inside the triangle
	return (u_bary >= 0 && v_bary >= 0 && (u_bary + v_bary) <= 1);

};



RenderAssist::~RenderAssist()
{
};

