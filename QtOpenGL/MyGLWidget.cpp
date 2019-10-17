#include "MyGLWidget.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QKeyEvent>

MyGLWidget::MyGLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      program(nullptr)
{
    translate = -6.0;
    xRot = 0.0;
    yRot = -30.0;
    zRot = 0.0;
}

void MyGLWidget::initializeGL()
{
    // 为当前环境初始化 OpenGL 函数
    initializeOpenGLFunctions();

    // 初始化纹理贴图
    textures[0] = new QOpenGLTexture(QImage(":/Resources/Front.png").mirrored());   // Front
    textures[1] = new QOpenGLTexture(QImage(":/Resources/Back.png").mirrored());    // Back
    textures[2] = new QOpenGLTexture(QImage(":/Resources/Left.png").mirrored());    // Left
    textures[3] = new QOpenGLTexture(QImage(":/Resources/Right.png").mirrored());   // Right
    textures[4] = new QOpenGLTexture(QImage(":/Resources/Up.png").mirrored());      // Up
    textures[5] = new QOpenGLTexture(QImage(":/Resources/Down.png").mirrored());    // Down

    // 创建顶点着色器
    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc =
            "#version 460                                  \n"
            "in vec4 vPosition;                            \n"
            "in vec2 vTexCoord;                            \n"
            "out vec2 texCoord;                            \n"
            "uniform mat4 matrix;                          \n"
            "void main() {                                 \n"
            "   texCoord = vTexCoord;                      \n"
            "   gl_Position = matrix * vPosition;          \n"
            "}                                             \n";
    vshader->compileSourceCode(vsrc);   // 编译顶点着色器源码

    // 创建片段着色器
    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc =
            "#version 460                                   \n"
            "uniform sampler2D tex;                         \n"
            "in vec2 texCoord;                              \n"
            "out vec4 fColor;                               \n"
            "void main() {                                  \n"
            "   fColor = texture(tex, texCoord);            \n"
            "}                                              \n";
    fshader->compileSourceCode(fsrc);   // 编译片段着色器源码

    program = new QOpenGLShaderProgram;     // 创建着色器程序
    program->addShader(vshader);            // 添加顶点着色器
    program->addShader(fshader);            // 添加片段着色器
    program->link();                        // 链接着色器
    program->bind();                        // 绑定着色器
}

void MyGLWidget::paintGL()
{
    int w = width();
    int h = height();
//    int side = qMin(w, h);
//    // 设置视口大小为正方形
//    glViewport((w - side) / 2, (h - side) /2, side, side);

    // 清除颜色缓冲和深度缓冲，从而以清除屏幕
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 创建顶点数组
    GLfloat vertices[6][4][3] = {
        { {-1.0f, 1.0f, 1.0f}, {-1.0f, -1.0f, 1.0f}, {1.0f, -1.0f, 1.0f}, {1.0f, 1.0f, 1.0f} },         // Front
        { {1.0f, 1.0f, -1.0f}, {1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f} },     // Back
        { {-1.0f, 1.0f, -1.0f}, {-1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, 1.0f}, {-1.0f, 1.0f, 1.0f} },     // Left
        { {1.0f, 1.0f, 1.0f}, {1.0f, -1.0f, 1.0f}, {1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, -1.0f} },         // Right
        { {-1.0f, 1.0f, -1.0f}, {-1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, -1.0f} },         // Up
        { {-1.0f, -1.0f, 1.0f}, {-1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, -1.0f}, {1.0f, -1.0f, 1.0f} }      // Down
    };

    // 在 OpenGL 服务端中创建缓存对象
    vbo.create();
    // 将与该对象相关联的缓存绑定到当前的 OpenGL 环境中
    vbo.bind();
    // 在缓存中为数组分配空间，并初始化为数组中的内容
    vbo.allocate(vertices, 120 * sizeof(GLfloat));

    // 返回其指定的变量，在着色器程序参数列表中的位置
    GLuint vPosition = program->attributeLocation("vPosition");

    // 此方法将 OpenGL 缓存中的数据与着色器中的数据进行关联
    program->setAttributeBuffer(vPosition, GL_FLOAT, 0, 3, 0);

    // 启用顶点着色器顶点数组
    glEnableVertexAttribArray(vPosition);



    // 定义纹理坐标
    GLfloat coords[6][4][2] = {
        { {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f} },
        { {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f} },
        { {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f} },
        { {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f} },
        { {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f} },
        { {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f} }
    };

    // 将颜色数据写入到缓存,第一个参数为偏移量，因为缓存前面已经存储了顶点数据
    vbo.write(72 * sizeof(GLfloat), coords, 48 * sizeof(GLfloat));

    // 返回着色器程序参数列表的位置
    GLuint vTexCoord = program->attributeLocation("vTexCoord");

    // 将缓存中的数据与着色器程序关联
    program->setAttributeBuffer(vTexCoord, GL_FLOAT, 72 * sizeof(GLfloat), 2, 0);

    // 启用片段着色器颜色数组
    glEnableVertexAttribArray(vTexCoord);
    // 初始化片段着色器中 tex 变量
    program->setUniformValue("tex", 0);

    // 创建 4 * 4 变换矩阵
    QMatrix4x4 matrix;
    matrix.perspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);

    matrix.translate(0, 0, translate);
    matrix.rotate(xRot, 1, 0, 0);
    matrix.rotate(yRot, 0, 1, 0);
    matrix.rotate(zRot, 0, 0, 1);

    program->setUniformValue("matrix", matrix);

    for(int i = 0; i < 6; i++) {
        textures[i]->bind();
        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
    }
}

void MyGLWidget::resizeGL(int width, int height)
{
    Q_UNUSED(width)
    Q_UNUSED(height)
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        xRot += 10;
        break;
    case Qt::Key_Left:
        yRot += 10;
        break;
    case Qt::Key_Right:
        zRot += 10;
        break;
    case Qt::Key_Down:
        translate -= 1;
        break;
    case Qt::Key_Space:
        translate += 1;
        break;
    default:
        break;
    }

    update();  // 更新显示
    QOpenGLWidget::keyPressEvent(event);
}
