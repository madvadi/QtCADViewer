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

	int num_crood = (int)ceil(9 * Ntrig);

	(*this).xyz_f = new float[num_crood];

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
	float x, y, z;

	fseek(PTRFILE, 0, SEEK_END);

	int size = ftell(PTRFILE);

	rewind(PTRFILE);
	fseek(PTRFILE, 0, SEEK_SET);

	char ch[100];

	fscanf(PTRFILE, "%s", ch);

	while (error != EOF)
	{
		error = fscanf(PTRFILE, "%s", ch);

		if (strstr(ch, "vertex") != NULL)
		{
			fscanf(PTRFILE, "%f %f %f", &x, &y, &z);

			(*this).xyz.push_back(x);
			(*this).xyz.push_back(y);
			(*this).xyz.push_back(z);

			i = i + 1;

			count = count + 1;
			if (count == 3) {

				tri_num = tri_num + 1;

				count = 0;
			}


		}
	}


};

void loadSTL::render()
{


	glBegin(GL_TRIANGLE_STRIP);

	for (int i = 0; i < tri_num * 9; i = i + 3)
	{
		//printf("x: %f y: %f z: %f \n",(*this).xyz[i],(*this).xyz[i+1],(*this).xyz[i+2]);
		glColor3f(1.0, 0.0, 1.0);


		glVertex3f((*this).xyz[i], (*this).xyz[i + 1], (*this).xyz[i + 2]);
	
	}

	glEnd();
};