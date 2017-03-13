#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H

#include <iostream>
#include <iomanip>

#include "definitions.h"

#include <QColor>
#include <QDebug>

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

static QString getVersionString(uint8_t version)
{
    return QString::number(static_cast<unsigned int>(version),16).toUpper();
}

static void logEvent(QString category, QString text)
{
    QString cat = ("["+category+"] ");
    // qDebug(output.toStdString().c_str());

    std::cout << std::setw(15) << cat.toStdString() << text.toStdString() << std::endl;
}


#endif // COMMONFUNCTIONS_H
