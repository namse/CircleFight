#pragma once
#include "..\..\PacketType\packet_type.pb.h"


/// DB 연결 스트링 
#define DB_CONN_STR "..\\Database\\user_example.db3"
#define LISTEN_PORT	9001

#define MAX_PKT_SIZE 1024

#define MAX_OBJECT 1024

const short	PKT_NONE = 0;
const short PKT_CS_LOGIN = 1;
const short	PKT_SC_LOGIN = 2;
const short	PKT_SC_LOGIN_BROADCAST = 3;
const short	PKT_CS_COLOR_CHANGE = 4;
const short	PKT_CS_MOVE_KEY_CHANGE = 5;
const short	PKT_SC_MOVE_START = 6;
const short	PKT_SC_MOVE_STOP = 7;
const short	PKT_SC_HP_CHANGE = 8;
const short	PKT_CS_ATTACK_KEY_CHANGE = 9;
const short	PKT_SC_ATTACK = 10;

struct PacketHeader{
	short size_;
	short type_;
	PacketHeader(short size, short type){
		size_ = size;
		type_ = type;
	}
	PacketHeader(short type){
		size_ = 0;
		type_ = type;
	}
	PacketHeader(){
		size_ = 0;
		type_ = 0;
	}
};

struct Packet
{
	PacketHeader packet_header_;
	unsigned char packet_data_ [MAX_PKT_SIZE];

	Packet(){
		packet_header_ = PacketHeader(PKT_NONE);
		memset(packet_data_, 0, sizeof(packet_data_));
	}

	Packet(short packet_type, ::google::protobuf::Message* packet_content){
		packet_header_ = PacketHeader(packet_content->ByteSize(), packet_type);
		packet_content->SerializeToArray(packet_data_, packet_header_.size_);
	}
};