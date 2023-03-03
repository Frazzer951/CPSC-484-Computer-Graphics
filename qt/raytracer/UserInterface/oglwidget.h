#ifndef OGLWIDGET_H
#define OGLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QOpenGLTexture>


class OglWidget : public QOpenGLWidget, protected QOpenGLFunctions {
public:
    OglWidget();
    ~OglWidget();

    void initializeGL();
    // void paintGL();
    void cleanup();

protected:
    QOpenGLContext* context;

private:
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;

    QOpenGLShaderProgram* program;
    QOpenGLShader* shader;
    QOpenGLTexture* texture;
};

#endif // OGLWIDGET_H
