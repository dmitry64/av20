#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdint.h>

struct Tact {
    uint8_t _CR;
    uint8_t _TR1;
    uint8_t _PULSER1;
    uint8_t _TR2;
    uint8_t _PULSER2;
    uint8_t _RESERVED;
};

struct TVG {
    uint8_t _samples[150];
};

struct AScanHeader {
    uint8_t _temp;
};

#endif // DEFINITIONS_H
