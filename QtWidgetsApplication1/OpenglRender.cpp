#include "OpenglRender.h"


QGL::QGL(QWidget* parent) : QOpenGLWidget(parent)
{

    view = 0.0f;

    polygonFace = GL_FRONT_AND_BACK;
    polygonMode = GL_LINE;

    matrixMode = GL_MODELVIEW;

    parClear = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

    matrix = new GLfloat[16];

    load.loadASCII("openfoamM.stl");

    view = 0.0f;


    /*
    for (int i = 0; i < 16; i++)
        matrix[i] = 0.0f;
    */
};

void QGL::initMatrixMode(GLenum matMode)
{
    matrixMode = matMode;

};

void QGL::initClear(GLenum pparClear)
{

    parClear = pparClear;

};

void QGL::addMatrix()
{

    glPushMatrix();

    // Transformations!
    glTranslatef(0.0f, 0.0f, view);

    glRotatef(45.0f, 1.0, 0.0, 0.0);
    glRotatef(45.0f, 0.0, 0.0, 1.0);

    glScalef(100.0f, 100.0f, 1.0f);


    //Get the Matrix before the finish initialisation!
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

    glPopMatrix();



};


void QGL::initPolygon(GLenum polFace, GLenum polMode)
{
    
    polygonFace = polFace;
    polygonMode = polMode;

};


float& QGL::return_view()
{
    return view;
};

void QGL::return_view(float increase)
{
    view = view + increase;
};

QGL::~QGL() {
};