#include "oglwidget.h"

OglWidget::OglWidget()
: QOpenGLWidget(), context(nullptr), program(nullptr), shader(nullptr), texture(nullptr) { }

OglWidget::~OglWidget() {
    makeCurrent();

    delete texture;
    delete shader;
    delete program;

    vbo.destroy();
    vao.destroy();
    doneCurrent();
}

void OglWidget::initializeGL() {
    initializeOpenGLFunctions();
}
//        glClearColor(1, 0, 0, 1);

//        vao.create();
//        if (vao.isCreated()) { vao.bind(); }

//        vbo.create();
//        vbo.bind();
//        vbo.allocate(...);
//        texture = new QOpenGLTexture(QImage(...));
//        shader = new QOpenGLShader(...);
//        program = new QOpenGLShaderProgram(...);
//}

// void OglWidget::paintGL();

void OglWidget::cleanup() { }
//        makeCurrent();
//        delete texture;
//        texture = nullptr;
    // ...
//        doneCurrent();
//}
