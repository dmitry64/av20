#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdint.h>
#include <vector>
#include <string>

#define MAX_CHANNELS_COUNT 8
#define MAX_TACTS_COUNT 8

#define TVG_SAMPLES_SIZE 200
#define TVG_SAMPLES_BYTES 175
#define TVG_MAX_DB 80
#define ASCAN_SAMPLES_SIZE 800
#define ASCAN_HEADER_SIZE 12

typedef uint16_t TactID;
typedef uint8_t ChannelID;
typedef uint8_t DeviceModeIndex;
typedef uint8_t SchemeIndex;
typedef uint8_t GateID;

struct CalibrationInfo{
    uint16_t _id;
    std::string _name;
};

typedef std::vector<CalibrationInfo> CalibrationsInfoList;

enum ModeTypes {
    Unknown,
    SearchMode,
    HandMode,
    HeadMode,
    WheelMode
};

enum TVGType {
    TVGSimple
};

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

#pragma pack(push, 1)
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
#pragma pack(pop)


struct BScanDrawSample {
    uint8_t _begin;
    uint8_t _end;
    uint8_t _level;
};

struct AScanDrawData {
    uint8_t _channel;
    uint16_t _markerPos;
    uint16_t _markerValue;
    std::vector<uint16_t> _samples;
};

struct BScanDrawData {
    uint8_t _channel;
    std::vector<BScanDrawSample> _samples;
};

struct DisplayPackage {
    AScanDrawData ascan;
    BScanDrawData bscan;
};

#pragma pack(push, 1)
struct AScan {
    AScanHeader _header;
    uint8_t _samples[800];
};
#pragma pack(pop)

struct Gate {
    uint16_t _start;
    uint16_t _finish;
    uint8_t _level;
    GateID _id;
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

static std::string FreqStrings[8] = {
    "1.0",
    "1.25",
    "2.0",
    "2.5",
    "4.0",
    "5.0",
    "8.0",
    "10.0"
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

static std::string ProgStrings[8] = {
    "Prog 1",
    "Prog 2",
    "Prog 3",
    "Prog 4",
    "Prog 5",
    "Prog 6",
    "Prog 7",
    "Prog 8"
};

#endif // DEFINITIONS_H
