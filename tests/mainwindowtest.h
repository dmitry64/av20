#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <QTest>
#include "ui/mainwindow.h"


class MainWindowTest : public QObject
{
    Q_OBJECT
public:
    explicit MainWindowTest(QObject *parent = 0);

signals:

public slots:

private slots:
    void simpleCreateTest();
    void simpleCreateWithCore();
    void simpleMenuClicking();
};

#endif // MAINWINDOWTEST_H
