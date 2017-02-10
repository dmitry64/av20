#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdint.h>

#define MAX_CHANNELS_COUNT 8
#define MAX_TACTS_COUNT 8

#define TVG_SAMPLES_SIZE 200
#define TVG_SAMPLES_BYTES 175
#define ASCAN_SAMPLES_SIZE 800
#define ASCAN_HEADER_SIZE 12

#define DEVICE_MODE_EVAL 0x00
#define DEVICE_MODE_SEARCH 0x01
#define DEVICE_MODE_HEAD_SCANNER 0x02
#define DEVICE_MODE_WHEEL 0x03

struct TactRegisters {
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

struct DeviceStatus {
    bool error;
    bool thsd;
    bool ready;
};

enum TriggerMode{
    PathTRG,
    TimeTRG,
    ExtTRG,
    ProgTRG
};

enum TVGMode {
    CurveMode,
    PointsMode,
    AutoMode
};

enum PulserFreq {
    Freq_1_0_MHz,
    Freq_1_25_MHz,
    Freq_2_0_MHz,
    Freq_2_5_MHz,
    Freq_4_0_MHz,
    Freq_5_0_MHz,
    Freq_8_0_MHz,
    Freq_10_0_MHz
};

enum PulserProg {
    Prog_1 = 0b0000,
    Prog_2 = 0b0001,
    Prog_3 = 0b0010,
    Prog_4 = 0b0011,
    Prog_5 = 0b0100,
    Prog_6 = 0b0101,
    Prog_7 = 0b0110,
    Prog_8 = 0b0111
};

#endif // DEFINITIONS_H
