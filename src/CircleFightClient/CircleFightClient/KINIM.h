#pragma once

#include "KINCommon.h"
#include "KINTM.h"

namespace KIN
{
	namespace Window
	{
		class KINWM;
	}

	namespace UserInterface
	{
		class KINUIEvent;
		class KINUIItem;
		class KINUIM;
	}

	namespace Input
	{
		namespace KeyCode
		{
			enum
			{
				KIN_Esc				= DIK_ESCAPE,

				KIN_0				= DIK_0,
				KIN_1				= DIK_1,
				KIN_2				= DIK_2,
				KIN_3				= DIK_3,
				KIN_4				= DIK_4,
				KIN_5				= DIK_5,
				KIN_6				= DIK_6,
				KIN_7				= DIK_7,
				KIN_8				= DIK_8,
				KIN_9				= DIK_9,

				KIN_NumLock			= DIK_NUMLOCK,
				KIN_Numpad_Subtract	= DIK_SUBTRACT,
				KIN_Numpad_Add		= DIK_ADD,
				KIN_Numpad_Decimal	= DIK_DECIMAL,
				KIN_Numpad_Enter	= DIK_NUMPADENTER,
				KIN_Numpad_Multiply	= DIK_MULTIPLY,
				KIN_Numpad_0		= DIK_NUMPAD0,
				KIN_Numpad_1		= DIK_NUMPAD1,
				KIN_Numpad_2		= DIK_NUMPAD2,
				KIN_Numpad_3		= DIK_NUMPAD3,
				KIN_Numpad_4		= DIK_NUMPAD4,
				KIN_Numpad_5		= DIK_NUMPAD5,
				KIN_Numpad_6		= DIK_NUMPAD6,
				KIN_Numpad_7		= DIK_NUMPAD7,
				KIN_Numpad_8		= DIK_NUMPAD8,
				KIN_Numpad_9		= DIK_NUMPAD9,

				KIN_A				= DIK_A,
				KIN_B				= DIK_B,
				KIN_C				= DIK_C,
				KIN_D				= DIK_D,
				KIN_E				= DIK_E,
				KIN_F				= DIK_F,
				KIN_G				= DIK_G,
				KIN_H				= DIK_H,
				KIN_I				= DIK_I,
				KIN_J				= DIK_J,
				KIN_K				= DIK_K,
				KIN_L				= DIK_L,
				KIN_M				= DIK_M,
				KIN_N				= DIK_N,
				KIN_O				= DIK_O,
				KIN_P				= DIK_P,
				KIN_Q				= DIK_Q,
				KIN_R				= DIK_R,
				KIN_S				= DIK_S,
				KIN_T				= DIK_T,
				KIN_U				= DIK_U,
				KIN_V				= DIK_V,
				KIN_W				= DIK_W,
				KIN_X				= DIK_X,
				KIN_Y				= DIK_Y,
				KIN_Z				= DIK_Z,

				KIN_F1				= DIK_F1,
				KIN_F2				= DIK_F2,
				KIN_F3				= DIK_F3,
				KIN_F4				= DIK_F4,
				KIN_F5				= DIK_F5,
				KIN_F6				= DIK_F6,
				KIN_F7				= DIK_F7,
				KIN_F8				= DIK_F8,
				KIN_F9				= DIK_F9,
				KIN_F10				= DIK_F10,
				KIN_F11				= DIK_F11,
				KIN_F12				= DIK_F12,
				KIN_F13				= DIK_F13,
				KIN_F14				= DIK_F14,
				KIN_F15				= DIK_F15,

				KIN_Minus			= DIK_MINUS,
				KIN_Equals			= DIK_EQUALS,
				KIN_Backspace		= DIK_BACK,
				KIN_Tab				= DIK_TAB,
				KIN_LBRacket		= DIK_LBRACKET,
				KIN_RBRacket		= DIK_RBRACKET,
				KIN_Enter			= DIK_RETURN,
				KIN_Semicolon		= DIK_SEMICOLON,
				KIN_Apostreophe		= DIK_APOSTROPHE,
				KIN_Grave			= DIK_GRAVE,
				KIN_Slash			= DIK_SLASH,
				KIN_Comma			= DIK_COMMA,
				KIN_Period			= DIK_PERIOD,
				KIN_BackSlash		= DIK_BACKSLASH,
				KIN_Space			= DIK_SPACE,

				KIN_Scroll			= DIK_SCROLL,

				KIN_Capital			= DIK_CAPITAL,
				KIN_LControl		= DIK_LCONTROL,
				KIN_RControl		= DIK_RCONTROL,
				KIN_LShift			= DIK_LSHIFT,
				KIN_RShift			= DIK_RSHIFT,
				KIN_LMenu			= DIK_LMENU,
				KIN_RMenu			= DIK_RMENU,

				KIN_Home			= DIK_HOME,
				KIN_PageUp			= DIK_PRIOR,
				KIN_PageDown		= DIK_NEXT,
				KIN_End				= DIK_END,
				KIN_Insert			= DIK_INSERT,
				KIN_Delete			= DIK_DELETE,

				KIN_Up				= DIK_UP,
				KIN_Down			= DIK_DOWN,
				KIN_Left			= DIK_LEFT,
				KIN_Right			= DIK_RIGHT,
			};
		}

		class Mouse
		{
		public:
			LPDIRECTINPUTDEVICE8 mDXInput_Mouse;
			DIMOUSESTATE mMouseState;

			Common::KINPoint mPoint;
			
			bool mLeftButton;
			bool mRightButton;
			bool mMiddleButton;

		public:
			Mouse(void);
			~Mouse(void);
		};
		class Keyboard
		{
		public:
			LPDIRECTINPUTDEVICE8 mDXInput_Keyboard;
			BYTE mKeyState[256];
			bool mKeyDownFlag[256];
			double mKeyTime[256];
			Time::KINTM mTimer;

			Keyboard(void);
			~Keyboard(void);

		public:
			bool IsKeyDown(const BYTE pKeyCode, const double pElapsed, const bool pbReset_WhenKeyUp = true);
			bool IsKeyUp(const BYTE pKeyCode);
		};

		class KINIM
		{
		private:
			Window::KINWM* mWM;
			LPDIRECTINPUT8 mDXInput;
			
		public:
			Mouse mMouse;
			Keyboard mKeyboard;

		public:
			KINIM(void);
			KINIM(Window::KINWM* pWM);
			~KINIM(void);

		public:
			void Init(Window::KINWM* pWM);
			void Detect(void);
			void Release(void);
		};
	}
}