#include <iostream>
#include <qdebug.h>

#include "RenderAssist.h"




RenderAssist::RenderAssist()
{

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			x[i][j] = 0.0f;

			dx[i][j] = 0.0;
		}
	}

};


RenderAssist::RenderAssist(RenderAssist* second)
{

	if (second == nullptr)
	{

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				x[i][j] = (*second).x[i][j];
				dx[i][j] = (*second).dx[i][j];
			}
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

// Function to calculate dot product of two vectors
double RenderAssist::dotProduct(double v1[3], double v2[3]) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
};

// Function to subtract two vectors
void RenderAssist::subtractVectors(double v1[3], double v2[3], double* temp) {

	temp[0] = v1[0] - v2[0];
	temp[1] = v1[1] - v2[1];
	temp[2] = v1[2] - v2[2];
};

// Function to subtract two vectors
void RenderAssist::subtractVectors(float v1[3], float v2[3], float* temp) {

	temp[0] = v1[0] - v2[0];
	temp[1] = v1[1] - v2[1];
	temp[2] = v1[2] - v2[2];
};

	


// Function to subtract two vectors
double* RenderAssist::subtractVectors(double v1[3], double v2[3]) {

	double temp[3] = { v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2] };

	return temp;
};


double RenderAssist::dotProduct2D(double v1[3], double v2[3]) {
	return v1[0] * v2[0] + v1[1] * v2[1];
};

// Function to subtract two vectors
double* RenderAssist::subtractVectors2D(double v1[3], double v2[3]) {

	double temp[3] = { v1[0] - v2[0], v1[1] - v2[1] };

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
	float u[3] = { 0.0f,0.0f,0.0f };
	subtractVectors((*this).x[1], (*this).x[0], u);

	float v[3] = { 0.0f,0.0f,0.0f };
	subtractVectors((*this).x[2], (*this).x[0], v);

	float vec[3] = { x,y,z };
	float w[3] = { 0.0f,0.0f,0.0f };
	subtractVectors(vec, (*this).x[0], w);

	// Calculate dot products
	float uu = dotProduct(u, u);
	float uv = dotProduct(u, v);
	float vv = dotProduct(v, v);
	float uw = dotProduct(u, w);
	float vw = dotProduct(v, w);

	// Calculate barycentric coordinates
	float denom = uu * vv - uv * uv;

	float u_bary = (vv * uw - uv * vw) / denom;
	float v_bary = (uu * vw - uv * uw) / denom;

	// Check if the point is inside the triangle
	bool bswitch = (u_bary >= 0.0f && v_bary >= 0.0f && (u_bary + v_bary) < 1.0f);

	return bswitch;


};

bool RenderAssist::isPointInsideTriangle3D(double x, double y, double z) {
	// Calculate vectors
	double u[3] = { 0.0,0.0,0.0 };
	subtractVectors((*this).dx[2], (*this).dx[0],u);

	double v[3] = { 0.0,0.0,0.0 };
	subtractVectors((*this).dx[1], (*this).dx[0],v);

	double vec[3] = { x,y,z };
	double w[3] = { 0.0,0.0,0.0 };
	subtractVectors(vec, (*this).dx[0],w);

	// Calculate dot products
	double uu = dotProduct(u, u);
	double uv = dotProduct(u, v);
	double vv = dotProduct(v, v);
	double uw = dotProduct(u, w);
	double vw = dotProduct(v, w);

	// Calculate barycentric coordinates
	double denom =  uu * vv - uv * uv;
	if (denom > 0.0)
	{
		double u_bary = (vv * uw - uv * vw ) / denom;
		double v_bary = (uu * vw - uv * uw) / denom;

		// Check if the point is inside the triangle
		bool bswitch = (u_bary >= 0.0 && v_bary >= 0.0 && (u_bary + v_bary) <= 1.0);

		return bswitch;
	}
	else
		return false;
	

};



RenderAssist::~RenderAssist()
{
};

