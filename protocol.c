#include "protocol.h"

CastPacket pack_RUFShare_CastPacket(RUFShareCRC16 crc) {
    CastPacket packet = {
        .type = htons(CAST),
        .pad0 = 0,
        .crc = htons(crc)
    };
    return packet;
}

FlowPacket pack_RUFShare_FlowPacket(RUFShareChunkSize chunk_size, RUFShareSequence sequence, RUFShareCRC32 crc) {
    FlowPacket packet = {
        .type = htons(FLOW),
        .pad0 = 0,
        .chunk_size = htons(chunk_size),
        .sequence = htonl(sequence),
        .crc = htonl(crc)
    };
    return packet;
}

SendPacket pack_RUFShare_SendPacket(RUFShareChunkSize chunk_size, RUFShareChunkCount chunk_count, RUFSharePartialChunkSize partial_chunk_size, RUFShareCRC16 crc) {
    SendPacket packet = {
        .type = htons(SEND),
        .pad0 = 0,
        .chunk_size = htons(chunk_size),
        .chunk_count = htonl(chunk_count),
        .partial_chunk_size = htons(partial_chunk_size),
        .crc = htons(crc)
    };
    return packet;
}

RecvPacket pack_RUFShare_RecvPacket(RUFShareACK ack, RUFShareCRC16 crc, RUFShareSequence sequence) {
    RecvPacket packet = {
        .type = htons(RECV),
        .ack = htons(ack),
        .crc = htons(crc),
        .sequence = htonl(sequence)
    };
    return packet;
}

CastPacket convert_CastPacket_byteorder(CastPacket* packet) {
    CastPacket new_packet = {
        .type = ntohs(packet->type),
        .pad0 = 0,
        .crc = ntohs(packet->crc)
    };
    return new_packet;
}

FlowPacket convert_FlowPacket_byteorder(FlowPacket* packet) {
    FlowPacket new_packet = {
        .type = ntohs(packet->type),
        .pad0 = 0,
        .chunk_size = ntohs(packet->chunk_size),
        .sequence = ntohl(packet->sequence),
        .crc = ntohl(packet->crc)
    };
    return new_packet;
}

SendPacket convert_SendPacket_byteorder(SendPacket* packet) {
    SendPacket new_packet = {
        .type = ntohs(packet->type),
        .pad0 = 0,
        .chunk_size = ntohs(packet->chunk_size),
        .chunk_count = ntohl(packet->chunk_count),
        .partial_chunk_size = ntohs(packet->partial_chunk_size),
        .crc = ntohs(packet->crc)
    };
    return new_packet;
}

RecvPacket convert_RecvPacket_byteorder(RecvPacket* packet) {
    RecvPacket new_packet = {
        .type = ntohs(packet->type),
        .ack = ntohs(packet->ack),
        .crc = ntohs(packet->crc),
        .sequence = ntohl(packet->sequence)
    };
    return new_packet;
}
