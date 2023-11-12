#pragma once
#ifndef _OPENGLRENDER_H_
#define _OPENGLRENDER_H_


#include <QtOpenGL>
#include <gl\GLU.h>
#include <glm\vec3.hpp> //
#include <glm\glm.hpp>  //
#include "qopengl.h"
#include <qopenglwidget.h>
#include <qopenglfunctions.h>
#include <qkeysequence.h>
#include <qtimer.h>

#include "KeyEnterReceiver.h"


#include "Load.h"

class QGL : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:

    QGL(float x, float y, QWidget* parent = nullptr);

    void initColor(float r, float g, float b);

    void addMatrix();

    void initClear(GLenum pparClear);

    void initPolygon(GLenum polFace, GLenum polMode);

    void initMatrixMode(GLenum matMode);

    void return_view_x(float increase);

    void return_view_y(float increase);

    void return_view_z(float increase);

    float& return_view();

    void return_view(float increase);

    void render_sphere(float x, float y, float z, float radius, int vCount);

    void render_star(float x, float y, float z, float size);

    void render_star(double x, double y, double z, double size);

    void project_cursor();

    void get_croodinate_windows();

    void multiplyMatrices(const float* matrix1, const float* matrix2, float* result);

    void selectTriangle(RenderAssist obj);

    ~QGL();

    KeyEnterReceiver* obj_key;

    vector<RenderAssist> triangles;

protected:


    void initializeGL() override
    {
        //tri_index.push_back(0);


        initializeOpenGLFunctions();

        camera();

        glClearColor(0.0, 0.0, 0.0, 0.0);  

    }

    void resizeGL(int w, int h) override
    {
        int tempx = w / 2;
        int tempy = h / 2;
        
        glViewport(-tempx, -tempy, w, h);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            // Handle or print the error

            qDebug() << "found a bug help!";
        }
        else
        {
            qDebug() << "tempx: " << tempx;
            qDebug() << "tempy: " << tempy;
            glGetIntegerv(GL_VIEWPORT, viewport);
            qDebug() << "viewports: ";
            qDebug() <<  viewport[0];
            qDebug() <<  viewport[1];
            qDebug() << viewport[2];
            qDebug() <<  viewport[3];

        }

    }

    void paintGL() override
    {

        glClear(parClear);

        camera();

        glMatrixMode(matrixMode);
       
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        glPolygonMode(polygonFace,polygonMode);

        glLoadIdentity();
        
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);        
        
        glPushMatrix();
        
        glTranslatef(view_x, view_y, 0.0f);

        glRotatef(anglex,0.0f,1.0f,0.0f);

        glRotatef(angley, 1.0f, 0.0f, 0.0f); 

        load.render(triangles);

        glPopMatrix();


        this->project_cursor();   


        for(int i = 0; i < tri_index.size(); i++)
            selectTriangle(triangles.at(i));


       
        glFlush();

    }

public slots:

    void animate()
    {
        xwin = this->width();
        ywin = this->height();

        // Convert the position to the OpenGL coordinate system.
        mx = ((2.0f * obj_key->return_x(this) / xwin) - 1.0f);
        my = (1.0f - (2.0f * obj_key->return_y(this) / ywin));

        // Grab the screen and move the scene around.
        if (obj_key->isLeftMouseButtonPressed == true)
        {
            // Clicked on something!

            camera_x = camera_x - (mx - pre_x)/ 10.0f;
            camera_y = camera_y - (my - pre_y)/ 10.0f;

        }


        pre_x = mx;
        pre_y = my;


        // Rotate the model.
        if (obj_key->isMiddleMouseButtonPressed == true)
        {
            anglex = anglex + (midx - mx)*100.0f;
            angley = angley + (midy - my)*100.0f;

        }

        midx = mx; 
        midy = my;


        // Control the zoom!        
        if (fabs(obj_key->return_angleWheel()) != 0.0f
            && view_z > 1.0f && view_z < 45.0f)
        {
            float _x = 0.01f;

            _x = copysignf(_x,obj_key->return_angleWheel());

            camera_x = camera_x + mx * _x;
            camera_y = camera_y + my * _x;

        }
        
        view_z = view_z - obj_key->return_angleWheel();

        obj_key->equal_angleWheel(0.0f);

        if (view_z <= 1.0f)
        {
            view_z = 1.0f;
        }
        else if (view_z >= 45.0f)
        {
            view_z = 45.0f;
        }

        for (int i = 0; i < triangles.size(); i++)
        {

            if (triangles.at(i).isPointInsideTriangle2D((float)posX, (float)posY, 0.0) == true)
            {
                tri_index.push_back(i);
            }

        }


        update();
    
    }

private:

    void camera()
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity(); 

        gluPerspective(/*45.0f */ view_z, (float)width() / (float)height(), 0.01f, 100.0f);



        gluLookAt(camera_x,camera_y, 1.0f,
            camera_x, camera_y, 0.0f,
            0.0f,  1.0f, 0.0f);

       // glGetFloatv(GL_PROJECTION_MATRIX, lookat);

        glGetDoublev(GL_PROJECTION_MATRIX, projection);


        project_y = tan(view_z*0.5f)*1.0f;

        project_x = project_y * (float)width() / (float)height();

        project_y = camera_y + project_y;

        project_x = camera_x + project_x;


    };

    float xwin;
    float ywin;

    GLenum polygonFace;
    GLenum polygonMode;

    GLenum matrixMode;

    GLenum parClear;

    //GLfloat* matrix;
    GLfloat matrix[16];

    GLfloat view[16];

    GLfloat lookat[16];

    GLint viewport[4];

    GLdouble projection[16];
    GLdouble modelview[16];


    GLdouble posX, posY, posZ;

    vector<int> tri_index;


    GLfloat delta;

    std::vector<GLfloat> glTrans3f[3];

    float view_x, view_y, view_z;


    float mx,my;

    float camera_x, camera_y;


    float project_y, project_x;

    float mousemovex,mousemovey;

    float pre_x, pre_y;

    GLfloat px, py, pz;

    float anglex, angley;

    float midx, midy;

    loadSTL load;
};


#endif