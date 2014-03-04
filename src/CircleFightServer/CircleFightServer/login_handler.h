#include "client_session.h"
#include "..\..\PacketType\packet_type.pb.h"
#include "circular_buffer.h"

void LoginRequestHandler(ClientSession* client_session_, LoginRequest in_packet);
