#include "txchannel.h"
#include <QDebug>

PulserFreq TxChannel::freq() const
{
    return _freq;
}

void TxChannel::setFreq(const PulserFreq &freq)
{
    _freq = freq;
}

PulserProg TxChannel::prog() const
{
    return _prog;
}

void TxChannel::setProg(const PulserProg &prog)
{
    _prog = prog;
}

bool TxChannel::doubleMode() const
{
    return _doubleMode;
}

void TxChannel::setDoubleMode(bool doubleMode)
{
    _doubleMode = doubleMode;
}

TxChannel::TxChannel() : _freq(PulserFreq::Freq_1_0_MHz), _prog(PulserProg::Prog_1), _doubleMode(false)
{

}

TxChannel::~TxChannel()
{

}

QDomElement TxChannel::generateXML(QDomDocument &doc) const
{
    QDomElement tx = doc.createElement("tx");

    QDomElement freq = doc.createElement("freq");
    freq.appendChild(doc.createTextNode(QString::number(_freq)));
    tx.appendChild(freq);

    QDomElement prog = doc.createElement("prog");
    prog.appendChild(doc.createTextNode(QString::number(_prog)));
    tx.appendChild(prog);

    QDomElement doubleMode = doc.createElement("doubleMode");
    doubleMode.appendChild(doc.createTextNode(QString::number(_doubleMode)));
    tx.appendChild(doubleMode);

    return tx;
}

void TxChannel::loadXML(const QDomNode &node)
{
    _freq = static_cast<PulserFreq>(node.firstChildElement("freq").text().toUInt());
    _prog = static_cast<PulserProg>(node.firstChildElement("prog").text().toUInt());
    _doubleMode = node.firstChildElement("doubleMode").text().toUInt();
}
