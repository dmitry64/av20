#include "bscanwidgetopengl.h"
/*#include "ui_bscanwidgetopengl.h"
#include <QOpenGLFunctions>

static const char *vertexShaderSource =
    "attribute highp vec4 posAttr;\n"
    "attribute lowp vec4 colAttr;\n"
    "varying lowp vec4 col;\n"
    "uniform highp mat4 matrix;\n"
    "void main() {\n"
    "   col = colAttr;\n"
    "   gl_Position = matrix * posAttr;\n"
    "}\n";

static const char *fragmentShaderSource =
    "varying lowp vec4 col;\n"
    "void main() {\n"
    "   gl_FragColor = col;\n"
    "}\n";

BScanWidgetOpenGL::BScanWidgetOpenGL(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::BScanWidgetOpenGL)
{
    ui->setupUi(this);
    m_frame = 0;
    m_posAttr = 0;
    m_colAttr = 0;
    m_matrixUniform = 0;
}

BScanWidgetOpenGL::~BScanWidgetOpenGL()
{
    delete ui;
}

void BScanWidgetOpenGL::initializeGL()
{

    m_program = new QOpenGLShaderProgram(this);
    Q_ASSERT(m_program);
    qDebug() << "init";
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    qDebug() << "linking";
    m_program->link();
    qDebug() << "linked";
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");
    qDebug() << "after";

}

void BScanWidgetOpenGL::resizeGL()
{

}

void BScanWidgetOpenGL::paintGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT);
    f->glViewport(0, 0, width(), height());

    f->glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);
    matrix.rotate(10.0f * m_frame, 0, 1, 0);

    m_program->setUniformValue(m_matrixUniform, matrix);

    GLfloat vertices[] = {
        -1.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, -1.0f
    };

    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    f->glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    f->glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);

    f->glDrawArrays(GL_TRIANGLES, 0, 3);


    f->glDisableVertexAttribArray(1);
    f->glDisableVertexAttribArray(0);

    m_program->release();
    m_frame++;
    update();
}

void BScanWidgetOpenGL::onBScan(BScanDrawData *scan)
{
    if(scan->_info._channel==0) {
        //_vertices.
        _scans.push_back(*scan);
    }
}
*/
