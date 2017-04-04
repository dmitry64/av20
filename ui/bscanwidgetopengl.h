#ifndef BSCANWIDGETOPENGL_H
#define BSCANWIDGETOPENGL_H
/*
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include "common/definitions.h"

namespace Ui
{
class BScanWidgetOpenGL;
}

class BScanWidgetOpenGL : public QOpenGLWidget
{
    Q_OBJECT

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;

    std::vector<BScanDrawData> _scans;

    std::vector<GLfloat> _vertices;
    std::vector<GLfloat> _colors;
public:
    explicit BScanWidgetOpenGL(QWidget *parent = 0);
    ~BScanWidgetOpenGL();
    void initializeGL();
    void resizeGL();
    void paintGL();
    void onBScan(BScanDrawData * scan);

private:
    Ui::BScanWidgetOpenGL *ui;
};*/

#endif // BSCANWIDGETOPENGL_H
