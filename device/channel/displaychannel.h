#ifndef DISPLAYCHANNEL_H
#define DISPLAYCHANNEL_H
#include "rxchannel.h"
#include "txchannel.h"
#include "device/definitions.h"
#include <QtXml/QDomElement>

class DisplayChannel
{
    RxChannel _rx;
    TxChannel _tx;
    std::vector<Gate> _gates;
    double _angle;
public:
    DisplayChannel();
    ~DisplayChannel();
    QDomElement generateXML(QDomDocument & doc) const;

    std::vector<Gate> gates() const;
    void setGates(const std::vector<Gate> &gates);
    double angle() const;
    void setAngle(double angle);
    RxChannel getRx() const;
    void setRx(const RxChannel &rx);
    TxChannel getTx() const;
    void setTx(const TxChannel &tx);
};

#endif // DISPLAYCHANNEL_H
