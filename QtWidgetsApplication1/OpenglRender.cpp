#include "OpenglRender.h"


QGL::QGL(float x, float y,QWidget* pptr_qwidget ,QWidget* parent) : QOpenGLWidget(parent)
{
    ptr_widget = pptr_qwidget;
    

    xwin = x;
    ywin = y;

    view_y = 0.0f;
    view_x = 0.0f;
    view_z = 90.0f;

    zNear = 0.50;
    zFar = 3.0;

    px = 0.0f;
    py = 0.0f;
    pz = 0.0f;

    posX = 0.0;
    posY = 0.0;
    posZ = 0.0;

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
    polygonMode =  GL_FILL;

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
    
    QPair<int,int> pair = this->format().version();

    qDebug() << "OpenGL version: " << pair;


    
    // Create a QSurfaceFormat object
    QSurfaceFormat format;

    // Set the desired OpenGL version
    format.setVersion(pair.first, pair.second); // For example, OpenGL 3.3

    format.setProfile(QSurfaceFormat::CoreProfile); // Use core profile
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer); // Enable double buffering
    format.setRenderableType(QSurfaceFormat::OpenGL);

    // Set other attributes as needed, such as depth buffer size, stencil buffer size, etc.
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);

    setFormat(format);

    
};


GLdouble QGL::return_posZ()
{

    return posZ;
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
   // glPushMatrix();

    glBegin(GL_QUADS);

    glColor3f(1.0f, 0.5f, 1.0f);
    glVertex3f(x-size*0.5f,y + size * 0.5f,z);
    glColor3f(0.5f, 1.0f, 1.0f);
    glVertex3f(x - size * 0.5f, y - size * 0.5f, z);
    glColor3f(0.5f, 1.0f, 1.0f);
    glVertex3f(x + size * 0.5f, y - size * 0.5f, z);
    glColor3f(1.0f, 0.5f, 1.0f);
    glVertex3f(x + size * 0.5f, y + size * 0.5f, z);

    glEnd();

    //glPopMatrix();

};


void QGL::render_star(double x, double y, double z, double size)
{

    glPushMatrix();
  
    glTranslated(x,y,z);
      
    glBegin(GL_QUADS);

    glColor3d(1.0, 1.0, 1.0);

    glVertex3d( -size * 0.5,-size * 0.5, 0.0);
    glColor3d(1.0, 1.0, 0.0);
    glVertex3d( -size * 0.5,  size * 0.5, 0.0);
    glColor3d(1.0, 1.0, 1.0);
    glVertex3d( size * 0.5,  size * 0.5, 0.0);
    glColor3d(1.0, 1.0, 0.0);
    glVertex3d( size * 0.5, -size * 0.5, 0.0);

    glEnd();

    glPopMatrix();
}

double convertZ(double n, double f, double z)
{
    // Convert Z from [0, 1] to [-1, 1]
    double wz = (2.0 * z) - 1.0;

    // Inverse projection matrix on the Z coordinate (assuming W=1)
    double a = -(f - n) / (2.0 * f * n);
    double b = (f + n) / (2.0 * f * n);
    return -1.0 / (wz * a + b);
}


double world_convertZ(double n, double f, double z)
{
    GLdouble clip_z = (z - 0.5) * 2.0;
    GLdouble world_z = 2 * f * n / (clip_z * (f - n) - (f + n));// ((f - n) / 2.0)* clip_z + (f + n) / 2.0;// 

    return world_z;
};


float world_convertZ(float n, float f, float z)
{
    GLfloat clip_z = (z - 0.5f) * 2.0f;
    GLfloat world_z = ((f - n) / 2.0f) * clip_z + (f + n) / 2.0f;

    return world_z;
};


void QGL::project_cursor()
{
    
    GLdouble winX, winY, winZ;

    GLfloat fwinZ = 0.0f;

    GLfloat depth_range[2] = {0.0f,0.0f};

    glGetFloatv(GL_DEPTH_RANGE,depth_range);

    /*
    winX = (GLdouble)obj_key->return_x(this) - viewport[2] / 2.0;
    winY =  viewport[3] / 2.0 - (GLdouble)obj_key->return_y(this);
    */
    winX = (GLdouble)obj_key->return_x(this);
    winY = viewport[3] - (GLdouble)obj_key->return_y(this);
    /*
    qDebug() << " winX: " << winX;
    qDebug() << " winY: " << winY;*/

    //glReadBuffer(GL_BACK);
    glReadPixels((int)winX , (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT , &fwinZ);

    qDebug() << " fwin_z: " << fwinZ;

    winZ = static_cast<GLdouble>(fwinZ);

    //qDebug() << " win_z: " << winZ;

    /*
    GLdouble world_z = world_convertZ(zNear, zFar, winZ);
    
    
    if(world_z != 0.0)
        qDebug() << " world Z: " << world_z;*/

    int tr = gluUnProject(winX , winY , winZ,
        modelview, projection, viewport,
        &posX, &posY, &posZ);

    GLuint error = glGetError();
    if (error != GL_NO_ERROR) {
        qDebug() << " GL_ERROR: " << error;
    }

    posZ = 1.0 - posZ;
/*
    qDebug() << " posZ: " << posZ;

   
    qDebug() << " winZ: " << winZ;

    qDebug() << " distance_posZ: " << convertZ(0.000001, 10000.0, posZ);

    qDebug() << " posZ: " << posZ;*/

   // this->render_star(posX, posY , posZ, 0.00001);


};


void QGL::selectTriangle(RenderAssist obj)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPushMatrix();

    glBegin(GL_TRIANGLES);

    glVertex3f(obj.x[0][0], obj.x[0][1], obj.x[0][2]);
    glVertex3f(obj.x[1][0], obj.x[1][1], obj.x[1][2]);
    glVertex3f(obj.x[2][0], obj.x[2][1], obj.x[2][2]);

    glEnd();

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

    glDeleteRenderbuffers(1, &depthBuffer);
    glDeleteFramebuffers(1, &fbo);
};