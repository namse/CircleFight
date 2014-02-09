#include "KINWM.h"

namespace KIN
{
	namespace Window
	{
		// Default Message Function
		LRESULT CALLBACK DefaultMessageFunction(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
		{
			switch(iMessage) {
			case WM_DESTROY:
				{
					PostQuitMessage(0);

					return 0;
				}
			}

			return (DefWindowProc(hWnd,iMessage,wParam,lParam));
		}

		KINWM::KINWM(void)
		{
			mhWnd = NULL;
		}
		KINWM::KINWM(const std::wstring& p_Caption,
							const Common::KINRect p_Rect,
							const unsigned int p_BackColor,
							const unsigned int p_WindowStyle,
							const WNDPROC p_MessageFunction)
		{
			if(!Create(p_Caption, p_Rect, p_BackColor, p_WindowStyle, p_MessageFunction))
			{
				printf("KINWM 생성자에서 Create 실패\n");
			}
		}
		KINWM::~KINWM(void)
		{
			SendMessage(mhWnd, WM_DESTROY, NULL, NULL);
		}
	
		bool KINWM::Create(const std::wstring& p_Caption,
							const Common::KINRect p_Rect,
							const unsigned int p_BackColor,
							const unsigned int p_WindowStyle,
							const WNDPROC p_MessageFunction)
		{
			mhInstance = GetModuleHandle(NULL);

			WNDCLASSW WndClass;
			WndClass.style			= CS_CLASSDC;
			WndClass.lpfnWndProc	= (WNDPROC)p_MessageFunction;
			WndClass.cbClsExtra		= 0;
			WndClass.cbWndExtra		= 0;
			WndClass.hInstance		= mhInstance;
			WndClass.hIcon			= LoadIcon (NULL, IDI_APPLICATION);
			WndClass.hCursor		= LoadCursor (NULL, IDC_ARROW);
			WndClass.hbrBackground	= 0;
			WndClass.lpszMenuName	= NULL;
			WndClass.lpszClassName	= p_Caption.c_str();
			RegisterClassW(&WndClass);

			mhWnd = CreateWindowW(p_Caption.c_str(), p_Caption.c_str(), p_WindowStyle,
								 p_Rect.mX, p_Rect.mY, p_Rect.mWidth, p_Rect.mHeight,
								 NULL, NULL, GetModuleHandle(NULL), NULL);

			if(mhWnd == NULL)
			{
				printf("KINWM::Create 실패 - mhWnd가 NULL 입니다.\n");
			}

			SetToClient(Common::KINSize(p_Rect.mWidth, p_Rect.mHeight));
		
			ShowWindow();

			return true;
		}
		void KINWM::Destroy(void)
		{
			SendMessage(mhWnd, WM_DESTROY, NULL, NULL);
			mhWnd = NULL;
		}

		HWND KINWM::GetHWND(void)
		{
			return mhWnd;
		}

		HINSTANCE KINWM::GetHINSTANCE(void)
		{
			return mhInstance;
		}

		void KINWM::SetToClient(Common::KINSize p_Size)
		{
			mClientSize = Common::KINSize(p_Size.mWidth, p_Size.mHeight);

			RECT ClientSize = {0, 0, mClientSize.mWidth, mClientSize.mHeight};
			AdjustWindowRect(&ClientSize, GetWindowLong(mhWnd, GWL_STYLE), false);
			mRect.mWidth = ClientSize.right - ClientSize.left;
			mRect.mHeight = ClientSize.bottom - ClientSize.top;
			SetWindowPos(mhWnd, NULL, 0, 0, mRect.mWidth, mRect.mHeight, SWP_NOMOVE);
		}

		void KINWM::ShowWindow(void)
		{
			if(mhWnd != NULL)
			{
				::ShowWindow(mhWnd, SW_SHOW);
			}
		}

		void KINWM::HideWindow(void)
		{
			if(mhWnd != NULL)
			{
				::ShowWindow(mhWnd, SW_HIDE);
			}
		}

		bool KINWM::PeekMsg(void)
		{
			MSG Message;

			if(PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
			{
				if(Message.message == WM_QUIT)
					return false;

				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}

			::Sleep(0);

			return true;
		}
	}
}