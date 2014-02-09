#pragma once

#include "KINCommon.h"

namespace KIN
{
	namespace Window
	{
		// Window's Styles
		namespace WMStyle
		{
			const static unsigned int   Default			= WS_OVERLAPPEDWINDOW;

			const static unsigned int   Titlebar		= WS_CAPTION;
			const static unsigned int   Close			= WS_SYSMENU;
			const static unsigned int   Maximizebox		= WS_MAXIMIZEBOX;
			const static unsigned int   Minimizebox		= WS_MINIMIZEBOX;

			const static unsigned int   Resize			= WS_THICKFRAME;
		}

		// Default Message Function
		LRESULT CALLBACK DefaultMessageFunction(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

		// ORG_Window
		class KINWM
		{
		private:
			HWND mhWnd;
			HINSTANCE mhInstance;
		public:
			Common::KINRect mRect;
			Common::KINSize mClientSize;

		public:
			KINWM(void);
			KINWM(const std::wstring& pCaption,
					 const Common::KINRect pRect,
					 const unsigned int pBackColor = RGB(255, 255, 255),
					 const unsigned int pWindowStyle = WMStyle::Close,
					 const WNDPROC pMessageFunction = (WNDPROC)DefaultMessageFunction);
			~KINWM(void);
		
			bool Create(const std::wstring& pCaption,
						const Common::KINRect pRect,
						const unsigned int pBackColor = RGB(255, 255, 255),
						const unsigned int pWindowStyle = WMStyle::Close,
						const WNDPROC pMessageFunction = (WNDPROC)DefaultMessageFunction);
			void Destroy(void);
			
			HWND GetHWND(void);
			HINSTANCE GetHINSTANCE(void);

			void SetToClient(Common::KINSize pRect);

			void ShowWindow(void);
			void HideWindow(void);

			bool PeekMsg(void);
		};
	}
}