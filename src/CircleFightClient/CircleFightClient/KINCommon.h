#pragma once

// If you want to hide console window, you can hide it by using "#define NON_CONSLE".
#ifdef NON_CONSOLE
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

// Include Windows
#include <Windows.h>
#include <Mmsystem.h>
#pragma comment(lib, "winmm")

// Include C/C++
#include <CStdio>
#include <CStdlib>
#include <Iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
using namespace std;

// Include DirectX
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// Include DirectInput
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace KIN
{
	namespace Common
	{
		// Make RGBA, ARGB, RGB
		inline unsigned int DX_RGBA(unsigned char R, unsigned char G, unsigned char B, unsigned char A)
		{
			return ((D3DCOLOR)((((A)&0xff)<<24)|(((R)&0xff)<<16)|(((G)&0xff)<<8)|((B)&0xff)));
		}
		inline unsigned int DX_ARGB(unsigned char A, unsigned char R, unsigned char G, unsigned char B)
		{
			return ((D3DCOLOR)((((A)&0xff)<<24)|(((R)&0xff)<<16)|(((G)&0xff)<<8)|((B)&0xff)));
		}
		inline unsigned int DX_RGB(unsigned char R, unsigned char G, unsigned char B)
		{
			return ((D3DCOLOR)((((0xff)&0xff)<<24)|(((R)&0xff)<<16)|(((G)&0xff)<<8)|((B)&0xff)));
		}

		class KINPoint
		{
		public:
			int mX;
			int mY;

		public:
			KINPoint(void) : mX(0), mY(0) {}
			KINPoint(const int pX, const int pY)
				: mX(pX), mY(pY) {}
			~KINPoint(void) {}
		};
	
		class KINSize
		{
		public:
			int mWidth;
			int mHeight;

		public:
			KINSize(void) : mWidth(0), mHeight(0) {}
			KINSize(const int pWidth, const int pHeight)
				: mWidth(pWidth), mHeight(pHeight) {}
			~KINSize(void) {}
		};
	
		class KINRect
		{
		public:
			int mX;
			int mY;
			int mWidth;
			int mHeight;

		public:
			KINRect(void) : mX(0), mY(0), mWidth(0), mHeight(0) {}
			KINRect(const int pX, const int pY, const int pWidth, const int pHeight)
				: mX(pX), mY(pY), mWidth(pWidth), mHeight(pHeight) {}
			~KINRect(void) {}
		};
	}
}