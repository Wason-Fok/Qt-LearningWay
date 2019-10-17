#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>    // 提供 OpenGL 缓存操作

class QOpenGLShaderProgram;
class QOpenGLTexture;

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MyGLWidget(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    QOpenGLShaderProgram *program;  // 创建着色器程序对象
    QOpenGLBuffer vbo;              // 创建 OpenGL 缓存对象

    QOpenGLTexture *textures[6];    // 创建 OpenGL 纹理贴图对象

    GLfloat translate, xRot, yRot, zRot;    // 模型偏移量

};

#endif // MYGLWIDGET_H
