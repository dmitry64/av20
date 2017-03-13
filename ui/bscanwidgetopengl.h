#ifndef BSCANWIDGETOPENGL_H
#define BSCANWIDGETOPENGL_H

#include <QWidget>
#include <QOpenGLWidget>

namespace Ui
{
class BScanWidgetOpenGL;
}

class BScanWidgetOpenGL : public QWidget
{
    Q_OBJECT

public:
    explicit BScanWidgetOpenGL(QWidget *parent = 0);
    ~BScanWidgetOpenGL();

private:
    Ui::BScanWidgetOpenGL *ui;
};

#endif // BSCANWIDGETOPENGL_H
