#include "OpenglRender.h"


QGL::QGL(float x, float y, QWidget* parent) : QOpenGLWidget(parent)
{

    obj_key= new KeyEnterReceiver;

    xwin = x;
    ywin = y;

    view_y = 0.0f;
    view_x = 0.0f;
    view_z = 90.0f;

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


void QGL::project_cursor()
{
    
    GLdouble winX, winY, winZ;

    

    winX = (GLdouble)obj_key->return_x(this) - viewport[2]/2.0;
    winY = viewport[3] / 2.0 - (GLdouble)obj_key->return_y(this);
   

    glReadPixels((int)winX, (int)winY, (GLsizei)project_x, (GLsizei)project_y, GL_DEPTH_COMPONENT, GL_DOUBLE, &winZ);

    int tr = gluUnProject(winX , winY , winZ,
        modelview, projection, viewport,
        &posX, &posY, &posZ);

    qDebug() << "posX: " << posX << " posY: " << posY << " posZ: " << posZ;

    this->render_star(posX, posY , posZ, 0.00001);

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
};