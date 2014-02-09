#include "KINIM.h"
#include "KINWM.h"

namespace KIN
{
	namespace Input
	{
		Mouse::Mouse(void)
			: mPoint(0, 0), mLeftButton(false), mRightButton(false), mMiddleButton(false)
		{
		}
		Mouse::~Mouse(void)
		{
		}
		
		Keyboard::Keyboard(void)
		{
			memset(mKeyState, 0, sizeof(BYTE)*256);
			memset(mKeyTime, 0, sizeof(double)*256);
			mTimer.Init();
		}
		Keyboard::~Keyboard(void)
		{
		}
		
		bool Keyboard::IsKeyDown(const BYTE pKeyCode, const double pElapsed, const bool pbReset_WhenKeyUp)
		{
			double tElapsed = mTimer.GetTime();

			if(mKeyState[pKeyCode] - 128 == 0)
			{
				if(tElapsed - mKeyTime[pKeyCode] >= pElapsed)
				{
					mKeyDownFlag[pKeyCode] = true;
					mKeyTime[pKeyCode] = tElapsed;

					return true;
				}
			}
			else if(pbReset_WhenKeyUp == true)
			{
				mKeyTime[pKeyCode] = 0;
			}

			return false;
		}
		bool Keyboard::IsKeyUp(const BYTE pKeyCode)
		{
			if(mKeyState[pKeyCode] - 128 == 0)
			{
				mKeyDownFlag[pKeyCode] = false;
				return true;
			}

			return false;
		}
		
		KINIM::KINIM(void)
		{
		}
		KINIM::KINIM(Window::KINWM* pWM)
		{
			Init(pWM);
		}
		KINIM::~KINIM(void)
		{
		}

		void KINIM::Init(Window::KINWM* pWM)
		{
			mWM = pWM;

			DirectInput8Create(mWM->GetHINSTANCE(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mDXInput, NULL);

			mDXInput->CreateDevice(GUID_SysKeyboard, &mKeyboard.mDXInput_Keyboard, NULL);
			mDXInput->CreateDevice(GUID_SysMouse, &mMouse.mDXInput_Mouse, NULL);

			mKeyboard.mDXInput_Keyboard->SetDataFormat(&c_dfDIKeyboard);
			mMouse.mDXInput_Mouse->SetDataFormat(&c_dfDIMouse);

			mKeyboard.mDXInput_Keyboard->SetCooperativeLevel(mWM->GetHWND(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
			mMouse.mDXInput_Mouse->SetCooperativeLevel(mWM->GetHWND(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		}

		void KINIM::Detect(void)
		{
			mKeyboard.mDXInput_Keyboard->Acquire();
			mMouse.mDXInput_Mouse->Acquire();
	
			if(mKeyboard.mDXInput_Keyboard->GetDeviceState(256, (LPVOID)mKeyboard.mKeyState) == DIERR_INPUTLOST)
			{
				mKeyboard.mDXInput_Keyboard->Acquire();
			}
			if(mMouse.mDXInput_Mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mMouse.mMouseState) == DIERR_INPUTLOST)
			{
				mKeyboard.mDXInput_Keyboard->Acquire();
			}

			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(mWM->GetHWND(), &pt);
			mMouse.mPoint.mX = pt.x;
			mMouse.mPoint.mY = pt.y;

			if(mMouse.mMouseState.rgbButtons[0] - 128 == 0)
			{
				mMouse.mLeftButton = true;
			}
			else
			{
				mMouse.mLeftButton = false;
			}

			if(mMouse.mMouseState.rgbButtons[1] - 128 == 0)
			{
				mMouse.mRightButton = true;
			}
			else
			{
				mMouse.mRightButton = false;
			}

			if(mMouse.mMouseState.rgbButtons[2] - 128 == 0)
			{
				mMouse.mMiddleButton = true;
			}
			else
			{
				mMouse.mMiddleButton = false;
			}
		}

		void KINIM::Release(void)
		{
			mKeyboard.mDXInput_Keyboard->Unacquire();
			mKeyboard.mDXInput_Keyboard->Release();
			mMouse.mDXInput_Mouse->Unacquire();
			mMouse.mDXInput_Mouse->Release();
			mDXInput->Release();
		}
	}
}