#ifndef CORETEST_H
#define CORETEST_H

#include <QtTest/QtTest>
#include <QObject>
#include "core.h"


class CoreTest : public QObject
{
    Q_OBJECT
private:

public:
    explicit CoreTest(QObject *parent = 0);
private slots:
    void coreCreate();
    /*void coreSimpleConfig();
    void coreCommunicationSimple();
    void coreGateSetup();
    void coreTvgSetup();*/

signals:

public slots:
};

#endif // CORETEST_H
