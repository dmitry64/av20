#ifndef CHANNEL_H
#define CHANNEL_H

#include <vector>
#include "stdint.h"

#include "device/tvg/tvgcurve.h"
#include "device/tvg/tvgtwopoints.h"
#include "device/tvg/tvgnpoints.h"
#include "common/definitions.h"
#include "common/commonfunctions.h"

#include <QtXml/QDomElement>

class RxChannel
{
    QString _name;
    uint8_t _prismTime;
    TVGCurve * _tvgCurve;
    int _markerPos;
    TVGCurve * generateTVGFromXML(const QDomNode &tvg);
public:
    RxChannel();
    RxChannel(const RxChannel & original);
    ~RxChannel();
    QDomElement generateXML(QDomDocument & doc) const;
    void loadXML(const QDomNode & node);
    RxChannel & operator=(const RxChannel &L);
    void setPrismTime(uint8_t prismTime);

    QString getName() const;
    void setName(const QString &name);
    int getMarkerPos() const;
    void setMarkerPos(int markerPos);
    const TVGCurve *getTvgCurve() const;
    void setTvgCurve(TVGCurve *tvgCurve);
    uint8_t getPrismTime() const;
};



#endif // CHANNEL_H
