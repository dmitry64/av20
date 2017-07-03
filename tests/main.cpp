#include <QApplication>
#include <QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "coretest.h"
#include "mainwindowtest.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTest::qExec(new CoreTest(), argc, argv);
    QTest::qExec(new MainWindowTest(), argc, argv);
    return 0;
}
