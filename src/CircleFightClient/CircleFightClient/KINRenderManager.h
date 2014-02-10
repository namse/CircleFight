#pragma once

#include "KINCommon.h"
#include "KINTimeManager.h"
#include "Texture.h"
#include "Animation.h"
#include "Font.h"

namespace KIN
{
	namespace Window
	{
		class KINWM;
	}

	namespace Render
	{
		class KINRenderManager
		{
			private:
				Window::KINWM*		mWM;

				bool					mIsWindowMode;
				LPDIRECT3D9				mpD3D;
				LPDIRECT3DDEVICE9		mpD3D_Device;
				LPD3DXSPRITE			mpD3D_Sprite;
				LPD3DXSPRITE			mpD3D_Font_Sprite;
				D3DPRESENT_PARAMETERS   mD3D_Present_Parameters;
				D3DDISPLAYMODE          mD3D_DisplayMode;
				WINDOWPLACEMENT			mWindowPlacement;

			public:
				KINRenderManager(void);
				KINRenderManager(const Window::KINWM& pWM, const bool& pIsWindowMode=true);
				~KINRenderManager(void);

			private:
				bool Init_Present_Parameters(void);
			public:
				bool Init(const Window::KINWM& pWM, const bool& pIsWindowMode=true);
				void Destroy(void);

			public:
				bool ResetDevice(void);
				void BeginDrawing(const unsigned int pColor = Common::DX_RGB(0, 0, 0));
				void EndDrawing(void);

				bool Capture(const std::wstring& pPath, const Common::KINRect& pRect = Common::KINRect(0, 0, 0, 0));

				bool CreateTexture(Texture& pTexture, const Common::KINSize pSize);
				bool LoadTextureInFile(Texture& pTexture, const std::wstring& pPath);
				bool LoadTextureInBytes(Texture& pTexture, void* pData, unsigned int pLenght, Common::KINSize pSize);
				bool LoadTextureInBytesInFile(Texture& pTexture, const std::wstring& pPath);
				
				bool DrawTexture(Texture& pTexture, const Common::KINPoint& pPoint, int pAlpha=255);
				bool DrawTexture(Texture& pTexture, const Common::KINPoint& pPoint, float pAngle, float pCenter_X, float pCenter_Y, int pAlpha=255);
				bool DrawTexture(Texture& pTexture, const Common::KINPoint& pPoint, float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y, int pAlpha=255);
				bool DrawTexture(Texture& pTexture, const Common::KINPoint& pPoint, float pAngle, float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y, int pAlpha=255);
				bool DrawTexture(Texture& pTexture, const Common::KINPoint& pPoint, const Common::KINRect& pRect, int pAlpha=255);
				bool DrawTexture(Texture& pTexture, const Common::KINPoint& pPoint, const Common::KINRect& pRect, float pAngle, float pCenter_X, float pCenter_Y, int pAlpha=255);
				bool DrawTexture(Texture& pTexture, const Common::KINPoint& pPoint, const Common::KINRect& pRect, float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y, int pAlpha=255);
				bool DrawTexture(Texture& pTexture, const Common::KINPoint& pPoint, const Common::KINRect& pRect, float pAngle, float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y, int pAlpha=255);
				
				bool DrawAnimation(Animation& pAnimation, const Common::KINPoint& pPoint, int pAlpha=255);
				bool DrawAnimation(Animation& pAnimation, const Common::KINPoint& pPoint, float pAngle, float pCenter_X, float pCenter_Y, int pAlpha=255);
				bool DrawAnimation(Animation& pAnimation, const Common::KINPoint& pPoint, float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y, int pAlpha=255);
				bool DrawAnimation(Animation& pAnimation, const Common::KINPoint& pPoint, float pAngle, float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y, int pAlpha=255);

				bool DrawString(const std::wstring& pFont, const Common::KINPoint& pPoint, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle, const unsigned int pColor);
				bool DrawString(const std::wstring& pFont, const Common::KINPoint& pPoint, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle, const unsigned int pColor, float pAngle, float pCenter_X, float pCenter_Y);
				bool DrawString(const std::wstring& pFont, const Common::KINPoint& pPoint, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle, const unsigned int pColor, float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y);
				bool DrawString(const std::wstring& pFont, const Common::KINPoint& pPoint, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle, const unsigned int pColor, float pAngle, float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y);
				bool DrawString(const std::wstring& pFont, const Common::KINRect& pRect, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle, const unsigned int pColor);
				bool DrawString(const std::wstring& pFont, const Common::KINRect& pRect, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle, const unsigned int pColor, float pAngle, float pCenter_X, float pCenter_Y);
				bool DrawString(const std::wstring& pFont, const Common::KINRect& pRect, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle, const unsigned int pColor, float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y);
				bool DrawString(const std::wstring& pFont, const Common::KINRect& pRect, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle, const unsigned int pColor, float pAngle, float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y);
				
				Common::KINRect CalcStringRect(const std::wstring& pFont, const Common::KINPoint& pPoint, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle);
				Common::KINRect CalcStringRect(const std::wstring& pFont, const Common::KINRect& pRect, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle);

				/*bool LoadUI(UI& pUI, const std::wstring& pPath);
				bool DrawUI(UI& pUI);*/
		};
	}
}