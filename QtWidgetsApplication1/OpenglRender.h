#pragma once
#ifndef _OPENGLRENDER_H_
#define _OPENGLRENDER_H_


#include "qopengl.h"
#include <qopenglwidget.h>
#include <qopenglfunctions.h>
#include <qkeysequence.h>
//#include <qtimer.h>

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
        this->addMatrix();        
    }

    void resizeGL(int w, int h) override
    {

        glViewport(0, 0, w, h);

    }

    void paintGL() override
    {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(parClear);

        glMatrixMode(matrixMode);

        glPolygonMode(polygonFace,polygonMode);

        glLoadIdentity();
        
        // Transformations!
        glLoadMatrixf(matrix);

        load.render();

    }

public slots:
    void animate()
    {
        update();
    }

private:


    GLenum polygonFace;
    GLenum polygonMode;

    GLenum matrixMode;

    GLenum parClear;

    GLfloat* matrix;

    std::vector<GLfloat> glTrans3f[3];

    float rotationAngle;

    float view;

    loadSTL load;
};


#endif