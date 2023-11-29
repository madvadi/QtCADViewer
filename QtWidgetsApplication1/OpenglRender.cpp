#include "OpenglRender.h"


QGL::QGL(float x, float y,QWidget* pptr_qwidget ,QWidget* parent) : QOpenGLWidget(parent)
{
    ptr_widget = pptr_qwidget;
    

    xwindow = x;
    ywindow = y;

    view_y = 0.0f;
    view_x = 0.0f;
    view_z = 90.0f;

    zNear = 0.7;
    zFar = 100.0;

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
    polygonMode = GL_FILL;

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

void QGL::multiplyMatrices(const double* matrix1, const double* matrix2, double* result) {

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; ++j)
        {
            result[i * 4 + j] = 0.0;
            for (int k = 0; k < 4; k = ++k)
            {
                result[i + j * 4] += matrix1[i  + k* 4]*matrix[k+j*4];

            }
        }
    }
};


void QGL::multiplyMatrixVector(const double* matrix1, double* vector)
{
    if (vector == NULL || matrix1 == NULL)
        return;

    vector[0] = matrix1[0] * vector[0] + matrix1[4] * vector[1] + matrix1[8] * vector[2] + matrix1[12] * vector[3];
    vector[1] = matrix1[1] * vector[0] + matrix1[5] * vector[1] + matrix1[9] * vector[2] + matrix1[13] * vector[3];
    vector[2] = matrix1[2] * vector[0] + matrix1[6] * vector[1] + matrix1[10] * vector[2] + matrix1[14] * vector[3];


};

void QGL::multiplyMatrixVector(const double* matrix1, double& posX, double& posY, double& posZ )
{
    if ( matrix1 == NULL)
        return;

    posX = matrix1[0] * posX + matrix1[4] * posY + matrix1[8] * posZ + matrix1[12] *1.0;
    posY = matrix1[1] * posX + matrix1[5] * posY + matrix1[9] * posZ + matrix1[13] *1.0;
    posZ = matrix1[2] * posX + matrix1[6] * posY + matrix1[10] * posZ + matrix1[14] * 1.0;

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
    GLdouble world_z = 2 * f * n / (clip_z * (f - n) - (f + n));//((f - n) / 2.0)* clip_z + (f + n) / 2.0;//
  

    return world_z;
};

double NDCZ(double n, double f, double z)
{
  
  

    return (z - 0.5) * 2.0;
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

    glViewport(-xwin/2,-ywin/2, xwin, ywin);

    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

    
    // Convert the position to the OpenGL coordinate system.
    mx = ( ( 2.0f*obj_key->return_x(this) / xwin) - 1.0f);
    my = (1.0f - (2.0f * obj_key->return_y(this) / ywin));

    winX = (GLdouble)obj_key->return_x(this);
    winY = ywin - (GLdouble)obj_key->return_y(this);

    qDebug() << "xwin = " << winX;
    qDebug() << "ywin = " << winY;
    
    glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &fwinZ);

    winZ = static_cast<GLdouble>(fwinZ);

    GLdouble adjustedDepth = NDCZ(zNear, zFar, winZ);

    glm::vec<4, GLdouble> ClipCoords(mx, my, adjustedDepth,1.0);

    //multiplyMatrices(projection, getmatrixofmodel,  result);
    glm::vec<4,int> viewportGLM = glm::make_vec4(viewport);
    glm::mat<4, 4, GLdouble> projGLM = glm::make_mat4x4(projection);
    glm::mat<4, 4, GLdouble> viewGLM = glm::make_mat4x4(modelview);

    
    glm::vec4 worldCoords = glm::inverse(projGLM*viewGLM)* ClipCoords;

    posX = worldCoords.x/ worldCoords.w;
    posY = worldCoords.y / worldCoords.w;
    posZ = worldCoords.z / worldCoords.w;


};

int QGL::addLayer(QString filename, int x, int y)
{
    //Needs Work
    icon.push_back(GLbitmap());

    icon.back().initial(filename,x,y);

    return 0;
};

int QGL::uiOverLay()
{
    //Needs Work

    glDisable(GL_DEPTH_TEST);

    for (int i = 0; i < icon.size(); i++)
    {
        glPushMatrix();

        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

        glm::mat4x4 modelviewGLM = glm::make_mat4x4(modelview);

        glm::vec<4, GLdouble> screen(icon.at(i).x+camera_x, icon.at(i).y + camera_y,0.0,0.0);

        screen = modelviewGLM * screen;
        glRasterPos2d(screen[0], screen[1]);

        glDrawPixels(icon.at(i).iconImage.width(), 
            icon.at(i).iconImage.height(), 
            GL_RGBA, GL_UNSIGNED_BYTE, 
            icon.at(i).iconImage.bits());

        glPopMatrix();
    }

    glEnable(GL_DEPTH_TEST);

    GLenum err = glGetError();

    return err;

};


void QGL::selectTriangle(RenderAssist obj)
{
    

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPushMatrix();

    glBegin(GL_TRIANGLES);

    glColor3f(0.0f,1.0f,1.0f);
    glVertex3f(obj.x[0][0], obj.x[0][1], obj.x[0][2]);
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(obj.x[1][0], obj.x[1][1], obj.x[1][2]);
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(obj.x[2][0], obj.x[2][1], obj.x[2][2]);

    glEnd();

    glPopMatrix();


};


void QGL::dselectTriangle(RenderAssist obj, double matrix[16])
{

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPushMatrix();

    glMultMatrixd(matrix);

    glTranslated(0.0,0.0, 0.001);

    glBegin(GL_TRIANGLES);

    for (int i = 0; i<3; i++)
    {
        glColor3d(1.0, 1.0, 1.0);
        glVertex3d(obj.dx[i][0], obj.dx[i][1], obj.dx[i][2]);

    }
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