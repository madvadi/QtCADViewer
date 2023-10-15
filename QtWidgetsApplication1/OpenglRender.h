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
        load.loadASCII("openfoamM.stl");

        view = 0.0f;

        initializeOpenGLFunctions();
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
        glTranslatef(0.0f, 0.0f, view);

        glRotatef(45.0f, 1.0, 0.0, 0.0);
        glRotatef(45.0f, 0.0, 0.0, 1.0);

        glScalef(100.0f, 100.0f, 1.0f);

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

    std::vector<GLfloat> glTrans3f[3];

    float rotationAngle;

    float view;

    loadSTL load;
};


#endif