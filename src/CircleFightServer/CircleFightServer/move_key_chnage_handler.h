#include "client_session.h"
#include "..\..\PacketType\packet_type.pb.h"
#include "circular_buffer.h"

void MoveKeyChangeHandler(ClientSession* client_session_, MoveKeyPressRequest in_packet);