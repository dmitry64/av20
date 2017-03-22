#include "displaychannel.h"
#include "device/tvg/tvgsinglepoint.h"

std::vector<Gate> DisplayChannel::gates() const
{
    return _gates;
}

void DisplayChannel::setGates(const std::vector<Gate> &gates)
{
    _gates = gates;
}

double DisplayChannel::angle() const
{
    return _angle;
}

void DisplayChannel::setAngle(double angle)
{
    _angle = angle;
}

RxChannel DisplayChannel::getRx() const
{
    return _rx;
}

void DisplayChannel::setRx(const RxChannel &rx)
{
    _rx = rx;
}

TxChannel DisplayChannel::getTx() const
{
    return _tx;
}

void DisplayChannel::setTx(const TxChannel &tx)
{
    _tx = tx;
}

DisplayChannel::DisplayChannel() : _angle(0)
{

}

DisplayChannel::~DisplayChannel()
{
    _gates.clear();
}

QDomElement DisplayChannel::generateXML(QDomDocument &doc) const
{
    QDomElement dispChannel = doc.createElement("displayChannel");

    QDomElement angle = doc.createElement("angle");
    angle.appendChild(doc.createTextNode(QString::number(_angle)));
    dispChannel.appendChild(angle);

    QDomElement rxElement = _rx.generateXML(doc);
    dispChannel.appendChild(rxElement);

    QDomElement txElement = _tx.generateXML(doc);
    dispChannel.appendChild(txElement);

    QDomElement gatesElement = doc.createElement("gates");
    for(auto it=_gates.begin(); it!=_gates.end(); it++) {
        const Gate & gate = it.operator *();
        QDomElement gateElement = doc.createElement("gate");

        QDomElement id = doc.createElement("id");
        id.appendChild(doc.createTextNode(QString::number(gate._id)));
        gateElement.appendChild(id);

        QDomElement start = doc.createElement("start");
        start.appendChild(doc.createTextNode(QString::number(gate._start)));
        gateElement.appendChild(start);

        QDomElement finish = doc.createElement("finish");
        finish.appendChild(doc.createTextNode(QString::number(gate._finish)));
        gateElement.appendChild(finish);

        QDomElement level = doc.createElement("level");
        level.appendChild(doc.createTextNode(QString::number(gate._level)));
        gateElement.appendChild(level);

        gatesElement.appendChild(gateElement);
    }
    dispChannel.appendChild(gatesElement);

    return dispChannel;
}
