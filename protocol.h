#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#define BROADCAST 0x11
#define FLOW 0x22
#define SEND 0x33
#define RECV 0x44

typedef uint8_t RUFSharePad;
typedef uint8_t RUFShareType;
typedef uint8_t RUFShareACK;
typedef uint16_t RUFShareChunkSize;
typedef uint16_t RUFSharePartialChunkSize;
typedef uint16_t RUFShareCRC16;
typedef uint32_t RUFShareSequence;
typedef uint32_t RUFShareCRC32;
typedef uint32_t RUFShareChunkCount;

typedef unsigned char Buffer;

typedef struct {
    RUFShareType type;
    RUFSharePad pad0;
    RUFShareCRC16 crc;
} BroadcastPacket;

typedef struct {
    RUFShareType type;
    RUFSharePad pad0;
    RUFShareChunkSize chunk_size;
    RUFShareSequence sequence;
    RUFShareCRC32 crc;
} FlowPacket;

typedef struct {
    RUFShareType type;
    RUFSharePad pad0;
    RUFShareChunkSize chunk_size;
    RUFShareChunkCount chunk_count;
    RUFSharePartialChunkSize partial_chunk_size;
    RUFShareCRC16 crc;
} SendPacket;

typedef struct {
    RUFShareType type;
    RUFShareACK ack;
    RUFShareCRC16 crc;
    RUFShareSequence sequence;
} RecvPacket;

#endif
