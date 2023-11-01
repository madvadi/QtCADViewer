#pragma once
#ifndef _OPENGLRENDER_H_
#define _OPENGLRENDER_H_


#include <QtOpenGL>
#include <gl\GLU.h>
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

    ~QGL();

    KeyEnterReceiver* obj_key;

protected:


    void initializeGL() override
    {

        initializeOpenGLFunctions();

        camera();

        glClearColor(0.0, 0.0, 0.0, 0.0);  

    }

    void resizeGL(int w, int h) override
    {

        glViewport(0, 0, w, h);

    }

    void paintGL() override
    {
      

        glClear(parClear);

        camera();

        glMatrixMode(matrixMode);

        glPolygonMode(polygonFace,polygonMode);

        glLoadIdentity();

        glTranslatef(view_x, view_y, 0.0f);

        load.render();

        glFlush();

    }

public slots:
    void animate()
    {
        xwin = this->width();
        ywin = this->height();

        if(obj_key->isLeftKeyPressed == true) 
            this->return_view_x(-0.01f);
        if(obj_key->isUpKeyPressed == true) 
            this->return_view_y(0.01f);
        if(obj_key->isRightKeyPressed == true) 
            this->return_view_x(0.01f);
        if(obj_key->isDownKeyPressed == true) 
            this->return_view_y(-0.01f);
        
        // Convert the position to the OpenGL coordinate system.
        mx = ((2.0f * obj_key->return_x() / xwin) - 1.0f);
        my = (1.0f - (2.0f * obj_key->return_y() / ywin));

        if (fabs(obj_key->return_angleWheel()) != 0.0f
            && view_z > 1.0f && view_z < 45.0f)
        {
            float _x = 0.01f;

            _x = copysignf(_x,obj_key->return_angleWheel());

            camera_x = camera_x + mx * _x;
            camera_y = camera_y + my* _x;

            qDebug() << "OpenGL Mouse position: " << camera_x << ", " << camera_y;
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

        update();
    
    }

private:

    void camera()
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity(); 

        gluPerspective(/*45.0f */ view_z, (float)width() / (float)height(), 0.01f, 100.0f);

        gluLookAt(camera_x, camera_y, 1.0f,
            camera_x, camera_y, 0.1f,
            0.0f,  1.0f, 0.0f);

    };

    float xwin;
    float ywin;

    GLenum polygonFace;
    GLenum polygonMode;

    GLenum matrixMode;

    GLenum parClear;

    //GLfloat* matrix;
    GLfloat matrix[16];

    GLfloat delta;

    std::vector<GLfloat> glTrans3f[3];

    float view_x, view_y, view_z;


    float mx,my;

    float camera_x, camera_y;


    loadSTL load;
};


#endif