#include "OpenglRender.h"


QGL::QGL(float x, float y, QWidget* parent) : QOpenGLWidget(parent)
{

    obj_key= new KeyEnterReceiver;

    xwin = x;
    ywin = y;

    view_y = 0.0f;
    view_x = 0.0f;
    view_z = 45.0f;

    px = 0.0f;
    py = 0.0f;
    pz = 0.0f;

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
    polygonMode =  GL_LINE;

    matrixMode = GL_MODELVIEW;

    parClear = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

    load.loadASCII("openfoamM.stl");    
   
    
    for (int i = 0; i < 16; i++) {
        matrix[i] = 0.0f;

        view[i] = 0.0f;

        lookat[i] = 0.0f;
    }

    
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(16); // 60 FPS


    setMouseTracking(true);

    //this->installEventFilter(obj_key);

    
};


void QGL::multiplyMatrices(const float* matrix1, const float* matrix2, float* result) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadMatrixf(matrix1);
    glMultMatrixf(matrix2);
    glGetFloatv(GL_MODELVIEW_MATRIX, result);
    glPopMatrix();
}


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

void QGL::render_sphere(float x, float y, float z, float radius, int vCount)
{

    float angle = 2.0f*3.14f/vCount;


    glBegin(GL_TRIANGLE_STRIP);
   
    glEnd();

};


void QGL::render_star(float x, float y, float z, float size)
{
    glPushMatrix();

    glBegin(GL_QUADS);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(x-size*0.5f,y + size * 0.5f,z);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(x - size * 0.5f, y - size * 0.5f, z);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(x + size * 0.5f, y - size * 0.5f, z);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(x + size * 0.5f, y + size * 0.5f, z);

    glEnd();

    glPopMatrix();

};


void QGL::render_star(double x, double y, double z, double size)
{
    glPushMatrix();

    glBegin(GL_QUADS);

    glColor3d(1.0, 1.0, 1.0);
    glVertex3d(x - size * 0.5, y + size * 0.5, z);
    glColor3d(1.0, 1.0, 1.0);
    glVertex3d(x - size * 0.5, y - size * 0.5, z);
    glColor3d(1.0, 1.0, 1.0);
    glVertex3d(x + size * 0.5, y - size * 0.5, z);
    glColor3d(1.0, 1.0, 1.0);
    glVertex3d(x + size * 0.5, y + size * 0.5, z);

    glEnd();

    glPopMatrix();

}


void QGL::project_cursor()
{
    
    // Convert to NDC
    float ndcX =  mx;//(2.0f * float(mx)) / float(width()) - 1.0f;
    float ndcY = my;//1.0f - (2.0f * float(my)) / float(height());
    
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLdouble winX, winY, winZ;
    float depth[2];
    GLdouble posX, posY, posZ;

    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    
    /*
    ndcY = viewport[3] - ndcY - 1;
    winX = (float)ndcX;
    winY = (float)ndcY;
    glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    gluUnProject(winX, winY, winZ, modelview,projection, viewport, &posX, &posY, &posZ);*/
    winX = (GLdouble)obj_key->return_x(this) -1.0;
    winY = (GLdouble)viewport[3] - (GLdouble)obj_key->return_y(this) -1.0;

    glReadPixels(winX, winY, 2, 2, GL_DEPTH_COMPONENT, GL_FLOAT, depth);


    gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &posX, &posY, &posZ);

    qDebug() << "posX: " << posX << " posY: " << posY << " posZ: " << posZ;

    this->render_star(posX, posY, posZ,0.001);

   this->render_star(0.5,0.0,0.0,0.01);

    this->render_star(-0.5, 0.0, 0.0, 0.01);

    /*
    float result[16] = {0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 
    0.0f, 0.0f, 0.0f, 0.0f, 
    0.0f, 0.0f, 0.0f, 0.0f };
    multiplyMatrices(lookat, view,result);


    float clipX = result[0] * ndcX + result[1] * ndcY + result[3];
    float clipY = result[4] * ndcX + result[5] * ndcY + result[7];
    float clipW = result[12] * ndcX + result[13] * ndcY + result[15];

    // Convert from clip coordinates to world coordinates
    float sceneX = clipX / clipW;
    float sceneY = clipY / clipW;

    // Place cursor on the back plate!
    this->render_star(sceneX, sceneY, 0.9f, 0.01f);*/

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