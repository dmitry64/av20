#ifndef TXCHANNEL_H
#define TXCHANNEL_H

#include "device/definitions.h"

#include <QtXml/QDomElement>

class TxChannel
{
    PulserFreq _freq;
    PulserProg _prog;
    bool _doubleMode;
public:
    TxChannel();
    ~TxChannel();
    QDomElement generateXML(QDomDocument & doc) const;
    void loadXML(const QDomNode & node);
    PulserFreq freq() const;
    void setFreq(const PulserFreq &freq);
    PulserProg prog() const;
    void setProg(const PulserProg &prog);
    bool doubleMode() const;
    void setDoubleMode(bool doubleMode);
};

#endif // TXCHANNEL_H
