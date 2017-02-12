#include "bscanwidgetopengl.h"
#include "ui_bscanwidgetopengl.h"

BScanWidgetOpenGL::BScanWidgetOpenGL(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BScanWidgetOpenGL)
{
    ui->setupUi(this);
}

BScanWidgetOpenGL::~BScanWidgetOpenGL()
{
    delete ui;
}
