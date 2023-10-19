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

#include "Load.h"

class QGL : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:


    QGL(QWidget* parent = nullptr);

    void initColor(float r, float g, float b);

    void addMatrix();

    void initClear(GLenum pparClear);

    void initPolygon(GLenum polFace, GLenum polMode);

    void initMatrixMode(GLenum matMode);

    float& return_view();

    void return_view(float increase);

    ~QGL();

protected:


    void initializeGL() override
    {

        initializeOpenGLFunctions();
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        //gluPerspective(45.0f, (float)width() / (float)height(), 0.01f, 100.0f);

        glOrtho(-10.0f, width() , -height(), 10.0f, -10.0f, 10.0f);

        gluLookAt(0.0f, 0.0f, 5.0f, 0.0, 0.0, -2.0, 0.0, 1.0, 0.0);
        
        this->addMatrix(); 
        
        glClearColor(0.0, 0.0, 0.0, 0.0);       
    }

    void resizeGL(int w, int h) override
    {

        glViewport(0, 0, w, h);

    }

    void paintGL() override
    {
        
        glClear(parClear);

        glMatrixMode(matrixMode);

        glPolygonMode(polygonFace,polygonMode);

        glLoadIdentity();
        
        // Transformations!
       // glLoadMatrixf(matrix);

      

        load.render();

    }

public slots:
    void animate()
    {
        view = view + delta;

        delta = 0.0f;

        update();
    }

private:


    GLenum polygonFace;
    GLenum polygonMode;

    GLenum matrixMode;

    GLenum parClear;

    GLfloat* matrix;

    GLfloat delta;

    std::vector<GLfloat> glTrans3f[3];

    float rotationAngle;

    float view;

    loadSTL load;
};


#endif