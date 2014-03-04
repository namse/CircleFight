#include "stdafx.h"
#include "packet_parse.h"

#include "login_handler.h"
#include "key_input_handler.h"

bool ParsePacket(ClientSession* client_session_, CircularBuffer& recv_buffer )
{
	while ( true )
	{
		char packet_data[MAX_PKT_SIZE];
		/// ��Ŷ ��� ũ�� ��ŭ �о�ͺ���
		PacketHeader packet_header = PacketHeader();
		if ( false == recv_buffer.Peek((char*)&packet_header, sizeof(packet_header) ) )
			return true ;


		/// ��Ŷ �ϼ��� �Ǵ°�? 
		if ( recv_buffer.GetStoredSize() < (packet_header.size_) )
			return true ;
		recv_buffer.Read((char*)&packet_header, sizeof(packet_header));
		recv_buffer.Read(packet_data, packet_header.size_);

		/// ��Ŷ �ڵ鸵
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
				/// ���� ������ �̻��� ��Ŷ �����Ŵ�.
				return false ;
			}
			break ;
		}
	}
	return true;
}