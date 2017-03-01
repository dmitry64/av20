#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H

#include "definitions.h"
#include <QColor>

static inline QColor getColorByLevel(uint8_t level) {
    if(level < 128) {
        if(level < 64) {
            return QColor(level*4,255,0);
        } else {
            return QColor(255,255-(level-64)*4,0);
        }
    } else {
        return QColor(255,0,0);
    }
}

static inline void setBit(uint8_t * ptr, int bit, uint8_t val) {
    uint8_t prev = ptr[bit/8];
    ptr[bit/8] |= (((prev >> (bit % 8)) | val) << (bit % 8));
}

static inline uint8_t getBitFromByteArray(uint8_t * ptr, int bit) {
    int b = bit / 8;
    return (ptr[b] >> (bit % 8)) & 0b00000001;
}


#endif // COMMONFUNCTIONS_H
