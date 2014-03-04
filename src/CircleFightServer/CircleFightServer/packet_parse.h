#include "client_session.h"
#include "..\..\PacketType\packet_type.pb.h"
#include "circular_buffer.h"

bool ParsePacket(ClientSession* client_session_, CircularBuffer& recv_buffer );