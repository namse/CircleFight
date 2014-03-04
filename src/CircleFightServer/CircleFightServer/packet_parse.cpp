#include "stdafx.h"
#include "packet_parse.h"

#include "login_handler.h"
#include "key_input_handler.h"

bool ParsePacket(ClientSession* client_session_, CircularBuffer& recv_buffer )
{
	while ( true )
	{
		char packet_data[MAX_PKT_SIZE];
		/// 패킷 헤더 크기 만큼 읽어와보기
		PacketHeader packet_header = PacketHeader();
		if ( false == recv_buffer.Peek((char*)&packet_header, sizeof(packet_header) ) )
			return true ;


		/// 패킷 완성이 되는가? 
		if ( recv_buffer.GetStoredSize() < (packet_header.size_) )
			return true ;
		recv_buffer.Read((char*)&packet_header, sizeof(packet_header));
		recv_buffer.Read(packet_data, packet_header.size_);

		/// 패킷 핸들링
		switch ( packet_header.type_ )
		{
		case PKT_CS_LOGIN:
			{
				LoginRequest in_packet;
				in_packet.ParseFromArray(packet_data, packet_header.size_);
				LoginRequestHandler(client_session_, in_packet);
			}
			break ;

		default:
			{
				/// 여기 들어오면 이상한 패킷 보낸거다.
				return false ;
			}
			break ;
		}
	}
	return true;
}