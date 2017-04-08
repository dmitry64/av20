#include "splashscreen.h"
#include "ui_splashscreen.h"

SplashScreen::SplashScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SplashScreen)
{
    ui->setupUi(this);
}

SplashScreen::~SplashScreen()
{
    delete ui;
}

void SplashScreen::progressChanged(int percent)
{
    ui->progressBar->setValue(percent);
    repaint();
    QApplication::processEvents();
}

void SplashScreen::setMessage(const QString &str)
{
    ui->groupBox->setTitle(str);
    repaint();
    QApplication::processEvents();
}
