#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QWidget>

namespace Ui
{
class SplashScreen;
}

class SplashScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SplashScreen(QWidget *parent = 0);
    ~SplashScreen();
public slots:
    void progressChanged(int percent);
    void setMessage(const QString & str);
private:
    Ui::SplashScreen *ui;
};

#endif // SPLASHSCREEN_H
