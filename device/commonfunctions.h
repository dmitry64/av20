#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H

#include <iostream>
#include <iomanip>

#include "definitions.h"
#include "tvg/tvgsinglepoint.h"

#include <QColor>
#include <QTime>
#include <QDebug>
#include <QtXml>

static inline QColor getColorByLevel(const uint8_t level)
{
    if(level < 128) {
        if(level < 64) {
            return QColor(level*4,255,0);
        }
        else {
            return QColor(255,255-(level-64)*4,0);
        }
    }
    else {
        return QColor(255,0,0);
    }
}

static inline void setBit(uint8_t * ptr, const int bit, const uint8_t val)
{
    uint8_t prev = ptr[bit/8];
    ptr[bit/8] |= (((prev >> (bit % 8)) | val) << (bit % 8));
}

static inline uint8_t getBitFromByteArray(const uint8_t * ptr, const int bit)
{
    return (ptr[bit / 8] >> (bit % 8)) & 0b00000001;
}

static inline QString getVersionString(uint8_t version)
{
    return "0x" + QString::number(static_cast<unsigned int>(version),16).toUpper() + " [" +QString::number(version)+"]";
}

static inline void logEvent(const QString & category,const QString & text)
{
    QString cat = ("["+category+"] ");
    QString time = "["+QTime::currentTime().toString("HH:mm:ss")+"]";
    std::cout << std::setw(10) << time.toStdString() << std::setw(15) << cat.toStdString() << text.toStdString() << std::endl;
}

static inline bool gateSorter(const Gate & a,const Gate & b)
{
    return (a._level<b._level);
}

static inline TVGCurve * generateTVGFromXML(const QDomNode &tvg)
{
    TVGCurve * result = 0;
    QDomElement element = tvg.toElement();
    qDebug() << "TVG";
    auto attribs = tvg.attributes();
    if(attribs.contains("type")) {
        qDebug() << "Contains!";
        QDomNode type = attribs.namedItem("type");
        qDebug() << type.toAttr().value();
        if(type.toAttr().value().compare("single") == 0) {
            double yBase = element.firstChildElement("yBase").text().toDouble();
            double xOffset = element.firstChildElement("xOffset").text().toDouble();
            double yHeight = element.firstChildElement("yHeight").text().toDouble();
            double xWidth = element.firstChildElement("xWidth").text().toDouble();
            double curve = element.firstChildElement("curve").text().toDouble();


            result = new TVGSinglePoint(yBase,xOffset,xWidth,yHeight,curve);
        }

    }

    Q_ASSERT(result);
    return result;
}

#endif // COMMONFUNCTIONS_H
