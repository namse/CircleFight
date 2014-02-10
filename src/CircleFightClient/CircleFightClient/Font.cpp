#include "KINRenderManager.h"
#include "KINWM.h"

namespace KIN
{
	namespace Render
	{
		map<wstring, ID3DXFont*> mFont;

		bool KINRenderManager::DrawString(const std::wstring& pFont, const Common::KINPoint& pPoint, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle, const unsigned int pColor)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || mpD3D_Font_Sprite == NULL)
			{
				return false;
			}

			mpD3D_Sprite->End();

			mpD3D_Font_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			RECT rt = {pPoint.mX, pPoint.mY, 0, 0};
			if(mFont[pFont] == NULL)
			{
				D3DXCreateFontW(mpD3D_Device, pSize, 0, pBold, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, pFont.c_str(), &mFont[pFont.c_str()]);
			}
			mFont[pFont.c_str()]->DrawText(mpD3D_Font_Sprite, pText.c_str(), -1, &rt, pStyle, pColor);

			mpD3D_Font_Sprite->End();
			
			mpD3D_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			return true;
		}
		bool KINRenderManager::DrawString(const std::wstring& pFont, const Common::KINPoint& pPoint, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle, const unsigned int pColor, float pAngle, float pCenter_X, float pCenter_Y)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || mpD3D_Font_Sprite == NULL)
			{
				return false;
			}

			mpD3D_Sprite->End();

			mpD3D_Font_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			if(pAngle != 0)
			{
				pAngle = D3DX_PI/(180/pAngle);
			}

			D3DXMATRIX mat;
			D3DXVECTOR2 mov((-(cos(pAngle)*pCenter_X-sin(pAngle)*pCenter_Y))+pPoint.mX+pCenter_X, (-(sin(pAngle)*pCenter_X+cos(pAngle)*pCenter_Y))+pPoint.mY+pCenter_Y);

			D3DXMatrixTransformation2D(&mat, NULL, NULL, NULL, NULL, pAngle, &mov);
			mpD3D_Font_Sprite->SetTransform(&mat);

			RECT rt = {pPoint.mX, pPoint.mY, 0, 0};
			if(mFont[pFont] == NULL)
			{
				D3DXCreateFontW(mpD3D_Device, pSize, 0, pBold, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, pFont.c_str(), &mFont[pFont.c_str()]);
			}
			mFont[pFont.c_str()]->DrawText(mpD3D_Font_Sprite, pText.c_str(), -1, &rt, pStyle, pColor);

			mpD3D_Font_Sprite->End();
			
			mpD3D_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			return true;
		}
		bool KINRenderManager::DrawString(const std::wstring& pFont, const Common::KINPoint& pPoint, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle, const unsigned int pColor, float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || mpD3D_Font_Sprite == NULL)
			{
				return false;
			}

			mpD3D_Sprite->End();

			mpD3D_Font_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			pCenter_X *= pScaling_Width;
			pCenter_Y *= pScaling_Height;

			D3DXMATRIX mat;
			D3DXVECTOR2 sc(pScaling_Width, pScaling_Height);

			D3DXMatrixTransformation2D(&mat, NULL, NULL, &sc, NULL, 0.f, NULL);
			mpD3D_Font_Sprite->SetTransform(&mat);

			RECT rt = {pPoint.mX, pPoint.mY, 0, 0};
			if(mFont[pFont] == NULL)
			{
				D3DXCreateFontW(mpD3D_Device, pSize, 0, pBold, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, pFont.c_str(), &mFont[pFont.c_str()]);
			}
			mFont[pFont.c_str()]->DrawText(mpD3D_Font_Sprite, pText.c_str(), -1, &rt, pStyle, pColor);

			mpD3D_Font_Sprite->End();
			
			mpD3D_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			return true;
		}
		bool KINRenderManager::DrawString(const std::wstring& pFont, const Common::KINPoint& pPoint, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle, const unsigned int pColor, float pAngle, float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || mpD3D_Font_Sprite == NULL)
			{
				return false;
			}

			mpD3D_Sprite->End();

			mpD3D_Font_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			if(pAngle != 0)
			{
				pAngle = D3DX_PI/(180/pAngle);
			}

			pCenter_X *= pScaling_Width;
			pCenter_Y *= pScaling_Height;

			D3DXMATRIX mat;
			D3DXVECTOR2 mov((-(cos(pAngle)*pCenter_X-sin(pAngle)*pCenter_Y))+pPoint.mX+pCenter_X, (-(sin(pAngle)*pCenter_X+cos(pAngle)*pCenter_Y))+pPoint.mY+pCenter_Y);
			D3DXVECTOR2 sc(pScaling_Width, pScaling_Height);

			D3DXMatrixTransformation2D(&mat, NULL, NULL, &sc, NULL, pAngle, &mov);
			mpD3D_Font_Sprite->SetTransform(&mat);

			RECT rt = {pPoint.mX, pPoint.mY, 0, 0};
			if(mFont[pFont] == NULL)
			{
				D3DXCreateFontW(mpD3D_Device, pSize, 0, pBold, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, pFont.c_str(), &mFont[pFont.c_str()]);
			}
			mFont[pFont.c_str()]->DrawText(mpD3D_Font_Sprite, pText.c_str(), -1, &rt, pStyle, pColor);

			mpD3D_Font_Sprite->End();
			
			mpD3D_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			return true;
		}
		bool KINRenderManager::DrawString(const std::wstring& pFont, const Common::KINRect& pRect, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle, const unsigned int pColor)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || mpD3D_Font_Sprite == NULL)
			{
				return false;
			}

			mpD3D_Sprite->End();

			mpD3D_Font_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			RECT rt = {pRect.mX, pRect.mY, pRect.mWidth, pRect.mHeight};
			if(mFont[pFont] == NULL)
			{
				D3DXCreateFontW(mpD3D_Device, pSize, 0, pBold, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, pFont.c_str(), &mFont[pFont.c_str()]);
			}
			mFont[pFont.c_str()]->DrawText(mpD3D_Font_Sprite, pText.c_str(), -1, &rt, pStyle, pColor);

			mpD3D_Font_Sprite->End();
			
			mpD3D_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			return true;
		}
		bool KINRenderManager::DrawString(const std::wstring& pFont, const Common::KINRect& pRect, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle, const unsigned int pColor, float pAngle, float pCenter_X, float pCenter_Y)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || mpD3D_Font_Sprite == NULL)
			{
				return false;
			}

			mpD3D_Sprite->End();

			mpD3D_Font_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			if(pAngle != 0)
			{
				pAngle = D3DX_PI/(180/pAngle);
			}

			D3DXMATRIX mat;
			D3DXVECTOR2 mov((-(cos(pAngle)*pCenter_X-sin(pAngle)*pCenter_Y))+pRect.mX+pCenter_X, (-(sin(pAngle)*pCenter_X+cos(pAngle)*pCenter_Y))+pRect.mY+pCenter_Y);

			D3DXMatrixTransformation2D(&mat, NULL, NULL, NULL, NULL, pAngle, &mov);
			mpD3D_Sprite->SetTransform(&mat);

			RECT rt = {pRect.mX, pRect.mY, pRect.mWidth, pRect.mHeight};
			if(mFont[pFont] == NULL)
			{
				D3DXCreateFontW(mpD3D_Device, pSize, 0, pBold, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, pFont.c_str(), &mFont[pFont.c_str()]);
			}
			mFont[pFont.c_str()]->DrawText(mpD3D_Font_Sprite, pText.c_str(), -1, &rt, pStyle, pColor);

			mpD3D_Font_Sprite->End();
			
			mpD3D_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			return true;
		}
		bool KINRenderManager::DrawString(const std::wstring& pFont, const Common::KINRect& pRect, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle, const unsigned int pColor, float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || mpD3D_Font_Sprite == NULL)
			{
				return false;
			}

			mpD3D_Sprite->End();

			mpD3D_Font_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			pCenter_X *= pScaling_Width;
			pCenter_Y *= pScaling_Height;

			D3DXMATRIX mat;
			D3DXVECTOR2 sc(pScaling_Width, pScaling_Height);

			D3DXMatrixTransformation2D(&mat, NULL, NULL, &sc, NULL, 0.f, NULL);
			mpD3D_Sprite->SetTransform(&mat);

			RECT rt = {pRect.mX, pRect.mY, pRect.mWidth, pRect.mHeight};
			if(mFont[pFont] == NULL)
			{
				D3DXCreateFontW(mpD3D_Device, pSize, 0, pBold, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, pFont.c_str(), &mFont[pFont.c_str()]);
			}
			mFont[pFont.c_str()]->DrawText(mpD3D_Font_Sprite, pText.c_str(), -1, &rt, pStyle, pColor);

			mpD3D_Font_Sprite->End();
			
			mpD3D_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			return true;
		}
		bool KINRenderManager::DrawString(const std::wstring& pFont, const Common::KINRect& pRect, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle, const unsigned int pColor, float pAngle, float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || mpD3D_Font_Sprite == NULL)
			{
				return false;
			}

			mpD3D_Sprite->End();

			mpD3D_Font_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			if(pAngle != 0)
			{
				pAngle = D3DX_PI/(180/pAngle);
			}

			pCenter_X *= pScaling_Width;
			pCenter_Y *= pScaling_Height;

			D3DXMATRIX mat;
			D3DXVECTOR2 mov((-(cos(pAngle)*pCenter_X-sin(pAngle)*pCenter_Y))+pRect.mX+pCenter_X, (-(sin(pAngle)*pCenter_X+cos(pAngle)*pCenter_Y))+pRect.mY+pCenter_Y);
			D3DXVECTOR2 sc(pScaling_Width, pScaling_Height);

			D3DXMatrixTransformation2D(&mat, NULL, NULL, &sc, NULL, pAngle, &mov);
			mpD3D_Sprite->SetTransform(&mat);

			RECT rt = {pRect.mX, pRect.mY, pRect.mWidth, pRect.mHeight};
			if(mFont[pFont] == NULL)
			{
				D3DXCreateFontW(mpD3D_Device, pSize, 0, pBold, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, pFont.c_str(), &mFont[pFont.c_str()]);
			}
			mFont[pFont.c_str()]->DrawText(mpD3D_Font_Sprite, pText.c_str(), -1, &rt, pStyle, pColor);

			mpD3D_Font_Sprite->End();
			
			mpD3D_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

			return true;
		}
		
		Common::KINRect KINRenderManager::CalcStringRect(const std::wstring& pFont, const Common::KINPoint& pPoint, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || mpD3D_Font_Sprite == NULL)
			{
				return Common::KINRect(0,0,0,0);
			}

			if(mFont[pFont] == NULL)
			{
				D3DXCreateFontW(mpD3D_Device, pSize, 0, pBold, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, pFont.c_str(), &mFont[pFont.c_str()]);
			}

			RECT rt = {pPoint.mX, pPoint.mY, 0, 0};
			mFont[pFont.c_str()]->DrawText(mpD3D_Font_Sprite, pText.c_str(), -1, &rt, DT_CALCRECT | pStyle, Common::DX_RGBA(255,255,255,255));
			
			return Common::KINRect(rt.left,rt.right,rt.right-rt.left,rt.bottom-rt.top);
		}
		Common::KINRect KINRenderManager::CalcStringRect(const std::wstring& pFont, const Common::KINRect& pRect, const std::wstring& pText, const unsigned int pSize, const unsigned int pBold, const unsigned int pStyle)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || mpD3D_Font_Sprite == NULL)
			{
				return Common::KINRect(0,0,0,0);
			}

			if(mFont[pFont] == NULL)
			{
				D3DXCreateFontW(mpD3D_Device, pSize, 0, pBold, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, pFont.c_str(), &mFont[pFont.c_str()]);
			}

			RECT rt = {pRect.mX, pRect.mY, pRect.mWidth, pRect.mHeight};
			mFont[pFont.c_str()]->DrawText(mpD3D_Font_Sprite, pText.c_str(), -1, &rt, DT_CALCRECT | pStyle, Common::DX_RGBA(255,255,255,255));
			
			return Common::KINRect(rt.left,rt.right,rt.right-rt.left,rt.bottom-rt.top);
		}
	}
}