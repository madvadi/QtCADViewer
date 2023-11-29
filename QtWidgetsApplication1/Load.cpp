#include <glm\vec3.hpp> 
#include <glm\glm.hpp>  
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\ext\matrix_projection.hpp>

#include "Load.h"



loadSTL::loadSTL()
{

	tri_num = 0;

	header_size = 0;

	(*this).xyz_f = NULL;

	cptr = NULL;

};
loadSTL::~loadSTL()
{

	if ((*this).xyz_f != NULL) delete[] (*this).xyz_f;
	if (cptr != NULL) delete[] cptr;

};


void loadSTL::loadBIN(const char* filename)
{

	//int error = 0;
	int count = 0;
	//int i = 0;

	FILE* PTRFILE = fopen(filename, "rb");

	fseek(PTRFILE, 0, SEEK_END);

	int size = ftell(PTRFILE);

	rewind(PTRFILE);

	cout << "The sizeof(uint8_t) = " << sizeof(uint8_t) << endl;

	fseek(PTRFILE, 80 * sizeof(char), SEEK_CUR);

	cout << "You are at this position: " << ftell(PTRFILE) << endl;

	if (fread(&Ntrig, sizeof(uint32_t), 1, PTRFILE) == 1) printf("The number of triangle is %u \n", Ntrig);
	else printf("couldn't find Ntrig = %i \n", Ntrig);

	cout << "You are at this position: " << ftell(PTRFILE) << endl;

	int num_coord = (int)ceil(9 * Ntrig);

	(*this).xyz_f = new float[num_coord];

	fseek(PTRFILE, 12 * sizeof(char), SEEK_CUR);

	cout << "You are at this position: " << ftell(PTRFILE) << endl;


	//while( count < 2/*Ntrig*/)
	for (int i = 0; i < 9 * Ntrig; i = i + 1)
	{
		//if(fread((*this).xyz_f,sizeof(float),9,PTRFILE)!=9) printf("fread has fucked up \n");

		if (fread(&(*this).xyz_f[i], sizeof(float), 1, PTRFILE) != 1) printf("fread has fucked up \n");

		if (count == 8)
		{
			fseek(PTRFILE, 14 * sizeof(char), SEEK_CUR);
			count = 0;
		}
		else
		{
			count = count + 1;
		}


	}
};


void loadSTL::loadASCII(const char* filename)
{

	FILE* PTRFILE = fopen(filename, "r");

	int error = 0;
	int i = 0;
	int count = 0;

	// buffer
	double x, y, z;

	fseek(PTRFILE, 0, SEEK_END);

	int size = ftell(PTRFILE);

	rewind(PTRFILE);
	fseek(PTRFILE, 0, SEEK_SET);

	char ch[100];

	(*this).xyz.resize(3);

	fscanf(PTRFILE, "%s", ch);

	while (error != EOF)
	{
		error = fscanf(PTRFILE, "%s", ch);

		if (strstr(ch, "vertex") != NULL)
		{
			fscanf(PTRFILE, "%lf %lf %lf", &x, &y, &z);

			(*this).xyz.at(0).push_back(x);
			(*this).xyz.at(1).push_back(y);
			(*this).xyz.at(2).push_back(z);

			i = i + 1;

			count = count + 1;
			if (count == 3) {

				tri_num = tri_num + 1;

				count = 0;
			}


		}
	}


};

void loadSTL::render(vector<RenderAssist>& RA_ptr, GLdouble posX,GLdouble posY,GLdouble posZ)
{

	GLfloat modelview[16];

	glGetFloatv(GL_MODELVIEW_MATRIX, modelview);

	glm::mat4x4 GLMmodelview = glm::make_mat4x4(modelview);

	glBegin(GL_TRIANGLES);		

	bool b = false;

	for (int i = 0; i < (tri_num) * 3; i = i + 3)
	{	
		
		RenderAssist temp;

		glm::vec<4, float> coord[3];

		coord[0] = glm::vec<4, float>((*this).xyz.at(0).at(i), (*this).xyz.at(1).at(i), (*this).xyz.at(2).at(i), 1.0);

		coord[0] = GLMmodelview * coord[0];

		coord[0] /= coord[0].w;

		temp.x[0][0] = coord[0].x;
		temp.x[0][1] = coord[0].y;
		temp.x[0][2] = coord[0].z;

		coord[1] = glm::vec<4, float>((*this).xyz.at(0).at(i+1), (*this).xyz.at(1).at(i+1), (*this).xyz.at(2).at(i+1), 1.0);

		coord[1] = GLMmodelview * coord[1];

		coord[1] /= coord[1].w;

		temp.x[1][0] = coord[1].x;
		temp.x[1][1] = coord[1].y;
		temp.x[1][2] = coord[1].z;

		coord[2] = glm::vec<4, float>((*this).xyz.at(0).at(i+2), (*this).xyz.at(1).at(i+2), (*this).xyz.at(2).at(i+2), 1.0);

		coord[2] = GLMmodelview * coord[2];

		coord[2] /= coord[2].w;


		temp.x[2][0] = coord[2].x;
		temp.x[2][1] = coord[2].y;
		temp.x[2][2] = coord[2].z;


		float col = 0.0f ;
		if (temp.isPointInsideTriangle3D((float)posX, (float)posY, (float)posZ)== true &&b==false)
		{

			col = 1.0f;
			b = true;	

			qDebug() << "i = " << i;

			qDebug() << "Coordinates pos transform: ";

			qDebug() << "posX = " << posX << " posY = " << posY << " posZ = " << posZ;

			for (int i_ = 0; i_ < 3; i_ = i_ + 1)
			{
				qDebug() << i_ <<" vector x = " << coord[i_].x << " y = " << coord[i_].y << " z = " << coord[i_].z;

				qDebug() << "Before trans. x = " << (*this).xyz.at(0).at(i+i_) << " y = " << (*this).xyz.at(1).at(i+i_) << " z = " << (*this).xyz.at(2).at(i+i_);

			}

	    }
		else
		{
			col = 0.7f;
		}
		//qDebug() << "posX = " << posX << " posY = " << posY << " posZ = " << posZ;

		glColor3f(col, col, col);

		glVertex3f((*this).xyz.at(0).at(i), (*this).xyz.at(1).at(i), (*this).xyz.at(2).at(i));

		glColor3f(col, col, col);

		glVertex3f((*this).xyz.at(0).at(i+1), (*this).xyz.at(1).at(i+1), (*this).xyz.at(2).at(i+1));

		glColor3f(col, col, col);

		glVertex3f((*this).xyz.at(0).at(i+2), (*this).xyz.at(1).at(i+2), (*this).xyz.at(2).at(i+2));

	}

	glEnd();

	glPolygonOffset(-2.5f, -2.5f);
	glLineWidth(2.0f);

	glBegin(GL_LINES); 

	for (int i = 0; i < (tri_num)*3-1; i = i + 1)
	{
		glColor3f(0.5f, 0.6f, 0.7f);
		glVertex3f((*this).xyz.at(0).at(i), (*this).xyz.at(1).at(i), (*this).xyz.at(2).at(i));
		glColor3f(0.5f, 0.6f, 0.7f);
		glVertex3f((*this).xyz.at(0).at(i + 1), (*this).xyz.at(1).at(i + 1), (*this).xyz.at(2).at(i + 1));

	}

	glEnd();


};