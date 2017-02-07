#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdint.h>

#define TVG_SAMPLES_SIZE 200
#define TVG_SAMPLES_BYTES 150
#define ASCAN_SAMPLES_SIZE 800
#define ASCAN_HEADER_SIZE 12

struct Tact {
    uint8_t _CR;
    uint8_t _TR1;
    uint8_t _PULSER1;
    uint8_t _TR2;
    uint8_t _PULSER2;
    uint8_t _RESERVED;
};

struct TVG {
    uint8_t _samples[TVG_SAMPLES_BYTES];
};


struct AScanHeader {
    uint8_t _frameMarker;
    uint8_t _descriptorSizeInBytes;
    uint8_t _tactNo;
    uint8_t _channelNo;
    uint8_t _dataType;
    uint8_t _dataWidth;
    uint16_t _samplesPerChannel;
    uint64_t _odoStamp;
};

struct AScan {
    AScanHeader _header;
    uint8_t _samples[800];
};

#endif // DEFINITIONS_H