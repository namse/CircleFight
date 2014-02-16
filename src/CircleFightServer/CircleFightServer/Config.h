#pragma once


/// DB 연결 스트링 
#define DB_CONN_STR "..\\Database\\user_example.db3"
#define LISTEN_PORT	9001

#define MAX_PKT_SIZE 1024

struct PacketHeader{
	short size;
	short type;
};

const int	PKT_NONE = 0;
const int 	PKT_CS_LOGIN = 1;
const int	PKT_SC_LOGIN = 2;
const int	PKT_SC_LOGIN_BROADCAST = 3;