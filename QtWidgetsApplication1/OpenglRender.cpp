#include "OpenglRender.h"


QGL::QGL(float x, float y, QWidget* parent) : QOpenGLWidget(parent)
{

    obj_key= new KeyEnterReceiver;

    xwin = x;
    ywin = y;

    view_y = 0.0f;
    view_x = 0.0f;
    view_z = 45.0f;

    mx = 0.0f;
    my = 0.0f;

    mousemovex = 0.0f;
    mousemovey = 0.0f;

    pre_x = 0.0f;
    pre_y = 0.0f;

    camera_x = 0.0f;
    camera_y = 0.0f;

    anglex = 0.0f; 
    angley = 0.0f;


    delta = 0.0f;

    polygonFace = GL_FRONT_AND_BACK;
    polygonMode = GL_LINE;

    matrixMode = GL_MODELVIEW;

    parClear = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

    load.loadASCII("openfoamM.stl");    
   
    
    for (int i = 0; i < 16; i++)
        matrix[i] = 0.0f;    

    
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(16); // 60 FPS

    
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

   glMatrixMode(matrixMode);

    glPushMatrix();

    // Transformations!
    glTranslatef(view_x, view_y, 0.0f);



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
    return view_x;
};

void QGL::return_view_x(float increase)
{
    view_x = view_x + increase;
};

void QGL::return_view_y(float increase)
{
    view_y = view_y + increase;
};

void QGL::return_view_z(float increase)
{
    view_z = view_z + increase;
};

QGL::~QGL() {
};