# RUFShare library
Reliable UDP File Sharing protocol, implemented exclusively for Cyphare

## Protocol Specification
RUFShare protocol splits into five types:  
- BROADCAST
- FLOW
- SEND
- RECV

#### RUFShare with type BROADCAST
```
 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|  type(0x11)   |      pad      |            CRC16              |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
.                          name@ip:port                         .
```
``` C
typedef struct {
    uint8_t type;
    uint8_t pad0;
    uint16_t crc;
} BroadcastPacket;
```
| Fields | describe |
|--------|----------|
| type  | value 0x11 for BROADCAST packets |
| CRC16 | CRC16 value of entire payload    |

#### RUFShare with type FLOW
```
 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|  type(0x22)   |      pad      |          chunk size           |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                            sequence                           |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                             CRC32                             |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
.                                                               .
.                              data                             .
.                                                               .
```
``` C
typedef struct {
    uint8_t type;
    uint8_t pad0;
    uint16_t chunk_size;
    uint32_t sequence;
    uint32_t crc;
} FlowPacket;
```
| Fields | describe |
|--------|----------|
|    type    | value 0x22 for FLOW packets   |
| chunk size | specifies chunk size in Byte  |
|  sequence  | specifies sequence of packets |
|    CRC32   | CRC32 value of entire packet  |

#### RUFShare with type SEND
```
 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|  type(0x33)   |      pad      |          chunk size           |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                         chunk count                           |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|      partial chunk size       |            CRC16              |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
.                          name@ip:port                         .
```
``` C
typedef struct {
    uint8_t type;
    uint8_t pad0;
    uint16_t chunk_size;
    uint32_t chunk_count;
    uint16_t partial_chunk_size;
    uint16_t crc;
} SendPacket;
```
| Fields | describe |
|--------|----------|
|        type        | value 0x33 for SEND packets  |
|     chunk size     | specifies chunk size in Byte |
|     chunk count    | number of fixed-size chunks  |
| partial chunk size | tail of file < chunk size    |
|        CRC16       | CRC16 value of entire packet |

#### RUFShare with type RECV
```
 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|  type(0x44)   | | | | | | | |A|            CRC16              |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                            sequence                           |
```
``` C
typedef struct {
    uint8_t type;
    uint8_t ack;
    uint16_t crc;
    uint32_t sequence;
} RecvPacket;
```
| Fields | describe |
|--------|----------|
|  type | value 0x44 for RECV packets  |
|  ACK  | 1 for ACK, 0 for NACK        |
| CRC16 | CRC16 value of entire packet |

