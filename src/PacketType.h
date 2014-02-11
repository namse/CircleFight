#pragma once
#include <time.h>

#define KEYSTATE_NOTPRESSED false
#define KEYSTATE_PRESSED true

#define MAX_PLAYER_LEN 20
#define MAX_NAME_LEN 20

#define PKT_NONE 0
#define PKT_CS_LOGIN 1
#define PKT_SC_LOGIN 2
#define PKT_SC_LOGIN_BROADCAST 3
#define PKT_CS_KEYSTATE 4
#define PKT_SC_KEYSTATE 5
#define PKT_SC_LOGOUT 6
#define PKT_CS_MOUSEANGLE 7
#define PKT_SC_MOUSEANGLE 8
#define PKT_SC_HP 9
#define PKT_SC_KILLSCORE 10
#define PKT_SC_ENDOFGAME 11

#define PKT_SC_A_TYPESKILL_SHOOT 12

#define PKT_SC_A_TYPEATTACK_SHOOT 13
#define PKT_SC_A_TYPEATTACK_END 14

#define PKT_SC_B_TYPESKILL_SHOOT 15

#define PKT_SC_B_TYPEATTACK_SHOOT 16
#define PKT_SC_B_TYPEATTACK_END 17

#define PKT_SC_C_TYPESKILL_SHOOT 18

#define PKT_SC_C_TYPEATTACK_SHOOT 19
#define PKT_SC_C_TYPEATTACK_END 20

#define PKT_SC_D_TYPESKILL_SHOOT 21
#define PKT_SC_D_TYPESKILL_END 22

#define PKT_SC_D_TYPEATTACK_SHOOT 23

#define PKT_SC_USERSKILL_FLASH 24
#define PKT_SC_USERSKILL_DASH 25

#define PKT_SC_PLAYER_KILLSCORE_UPDATE 26

struct Point
{
	Point()
	{

	}
	Point(float _x, float _y)
	{
		x = _x , y = _y;
	}
	Point operator+( const Point& point ) const{
		return Point(x+point.x,y+point.y);
	}
	Point operator-( const Point& point ) const{
		return Point(x+point.x,y+point.y);
	}
	Point operator*( float n ) const{
		return Point(x*n,y*n);
	}
	bool operator!=( const Point& point ) const{
		if( x == point.x && y == point.y)
			return false;
		return true;
	}
	bool operator==( const Point& point ) const{
		if( x == point.x && y == point.y)
			return true;
		return false;
	}
	float Distance(const Point& aPoint, const Point& bPoint) const {
		return (float)pow(pow(aPoint.x-bPoint.x,2) + pow(aPoint.y-bPoint.y,2),0.5);
	}
	Point Rotate(Point point, float angle) const {
	return Point(point.x * cos(angle) - point.y * sin(angle),
		point.x * sin(angle) + point.y * cos(angle));
	}
	float x,y;
};
struct GameKeyStates
{
	GameKeyStates()
	{
		upDirectKey = KEYSTATE_NOTPRESSED;
		downDirectKey = KEYSTATE_NOTPRESSED;
		leftDirectKey = KEYSTATE_NOTPRESSED;
		rightDirectKey = KEYSTATE_NOTPRESSED;
		attackKey = KEYSTATE_NOTPRESSED;
	}
	bool upDirectKey;
	bool downDirectKey;
	bool leftDirectKey;
	bool rightDirectKey;
	bool attackKey;
};

struct PlayerInfo
{
	float mX, mY, mAngle;
	int mPlayerId;
	short mPlayerState;
	int mHP;
	Point mMoveDirection;
	int mTeam;
	int mType;
	int mKillScore;
};
#pragma pack(push, 1)

struct PacketHeader
{
	PacketHeader() : mSize(0), mType(PKT_NONE) 	{}
	short mSize ;
	short mType ;
} ;

struct LoginRequest : public PacketHeader
{
	LoginRequest()
	{
		mSize = sizeof(LoginRequest);
		mType = PKT_CS_LOGIN;
	}
	wchar_t mName[MAX_NAME_LEN];
	short mCountry;
	short mRoomNumber;
};
struct LoginResult : public PacketHeader
{
	LoginResult()
	{
		mSize = sizeof(LoginResult);
		mType = PKT_SC_LOGIN;
	}
	int mMyPlayerId;
	int mKillLimit;
	int mNowPlayersLength;
	int mNowSkillsLength;
	int mNowBulletsLength;
	//PlayerInfo mPlayersInfo[];
	//BulletInfo mBulletInfo[];
	//SkillInfo mSkillInfo[];
};
struct LoginBroadcastResult : public PacketHeader
{
	LoginBroadcastResult()
	{
		mSize = sizeof(LoginBroadcastResult);
		mType = PKT_SC_LOGIN_BROADCAST;
	}
	PlayerInfo mPlayerInfo;
};
struct GameKeyStatesUpdateRequest : public PacketHeader
{
	GameKeyStatesUpdateRequest()
	{
		mSize = sizeof(GameKeyStatesUpdateRequest) ;
		mType = PKT_CS_KEYSTATE ;
		mPlayerId = -1 ;
	}
	int mPlayerId;
	GameKeyStates mGameKeyStates;
} ;

struct GameKeyStatesUpdateResult : public PacketHeader
{
	GameKeyStatesUpdateResult()
	{
		mSize = sizeof(GameKeyStatesUpdateResult) ;
		mType = PKT_SC_KEYSTATE ;
		mMyPlayerInfo.mPlayerId = -1 ;
	}
	PlayerInfo mMyPlayerInfo;
} ;
struct LogoutResult : public PacketHeader
{
	LogoutResult()
	{
		mSize = sizeof(LogoutResult);
		mType = PKT_SC_LOGOUT;
	}
	int mPlayerId;
};

struct MouseAngleUpdateRequest : public PacketHeader
{
	MouseAngleUpdateRequest()
	{
		mSize = sizeof(MouseAngleUpdateRequest);
		mType = PKT_CS_MOUSEANGLE;
	}
	int mPlayerId;
	float mAngle;
};

struct MouseAngleUpdateResult : public PacketHeader
{
	MouseAngleUpdateResult()
	{
		mSize = sizeof(MouseAngleUpdateResult);
		mType = PKT_SC_MOUSEANGLE;
	}
	int mPlayerId;
	float mAngle;
};


struct PlayerKillScoreUpdateResult : public PacketHeader
{
	PlayerKillScoreUpdateResult()
	{
		mSize = sizeof(PlayerKillScoreUpdateResult);
		mType = PKT_SC_PLAYER_KILLSCORE_UPDATE;
	}
	int mPlayerId;
	int mKillScore;
};

struct HPUpdateResult : public PacketHeader
{
	HPUpdateResult()
	{
		mSize = sizeof(HPUpdateResult);
		mType = PKT_SC_HP;
	}
	int mPlayerId;
	int mHP;
};

struct EndOfGameResult : public PacketHeader
{
	EndOfGameResult()
	{
		mSize = sizeof(EndOfGameResult);
		mType = PKT_SC_ENDOFGAME;
	}
	int mWinnerTeam;
};
#pragma pack(pop)