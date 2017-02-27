#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H

#include "definitions.h"
#include <QColor>

static QColor getColorByLevel(uint8_t level) {
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



#endif // COMMONFUNCTIONS_H
