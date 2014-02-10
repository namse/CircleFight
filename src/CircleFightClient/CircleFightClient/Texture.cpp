#include "KINRenderManager.h"
#include "KINWM.h"

namespace KIN
{
	namespace Render
	{
		Texture::Texture(void)
			: mpTexture(NULL), mSize(0, 0)
		{
		}

		Texture::~Texture(void)
		{
		}

		bool KINRenderManager::CreateTexture(Texture& pTexture, const Common::KINSize pSize)
		{
			int Width = 0, Height = 0;

			int i = 0;
			for(i = 0; true; ++i)
			{
				int tW = 1;

				int j = 0;
				for(j = 0; j < i; ++j)
				{
					tW *= 2;
				}

				if(tW <= pSize.mWidth && pSize.mWidth < tW*2)
				{
					Width = tW*2;
					break;
				}
			}

			for(i = 0; true; ++i)
			{
				int tH = 1;

				int j = 0;
				for(j = 0; j < i; ++j)
				{
					tH *= 2;
				}

				if(tH <= pSize.mHeight && pSize.mHeight < tH*2)
				{
					Height = tH*2;
					break;
				}
			}

			pTexture.mSize = pSize;
			mpD3D_Device->CreateTexture(Width, Height, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &pTexture.mpTexture, NULL);

			return true;
		}

		bool KINRenderManager::LoadTextureInFile(Texture& pTexture, const std::wstring& pPath)
		{
			D3DXIMAGE_INFO info;

			D3DXGetImageInfoFromFileW(pPath.c_str(), &info);

			if(FAILED(D3DXCreateTextureFromFileExW(mpD3D_Device, pPath.c_str(), info.Width, info.Height, 1, 0,
				D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &pTexture.mpTexture)))
			{
				return false;
			}

			pTexture.mSize.mWidth = info.Width;
			pTexture.mSize.mHeight = info.Height;

			return true;
		}
		bool KINRenderManager::LoadTextureInBytes(Texture& pTexture, void* pData, unsigned int pLenght, Common::KINSize pSize)
		{
			D3DXCreateTextureFromFileInMemoryEx(mpD3D_Device, pData, pLenght, pSize.mWidth, pSize.mHeight,
											1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT,
											D3DX_DEFAULT, 0, NULL, NULL, &pTexture.mpTexture);
			pTexture.mSize = pSize;

			return true;
		}
		bool KINRenderManager::LoadTextureInBytesInFile(Texture& pTexture, const std::wstring& pPath)
		{

			return true;
		}
		
		bool KINRenderManager::DrawTexture(Texture& pTexture, const Common::KINPoint& pPoint, int pAlpha)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || pTexture.mpTexture == NULL)
			{
				return false;
			}

			RECT rc = {0, 0, pTexture.mSize.mWidth, pTexture.mSize.mHeight};

			D3DXMATRIX mat;
			D3DXVECTOR2 mov(pPoint.mX, pPoint.mY);
			D3DXMatrixTransformation2D(&mat, NULL, NULL, NULL, NULL, 0.f, &mov);
			mpD3D_Sprite->SetTransform(&mat);
			
			D3DXVECTOR3 Pos(0, 0, 0);
			mpD3D_Sprite->Draw(pTexture.mpTexture, &rc, NULL, &Pos, Common::DX_RGBA(255, 255, 255, pAlpha));

			return true;
		}
		bool KINRenderManager::DrawTexture(Texture& pTexture, const Common::KINPoint& pPoint, float pAngle, float pCenter_X, float pCenter_Y, int pAlpha)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || pTexture.mpTexture == NULL)
			{
				return false;
			}

			RECT rc = {0, 0, pTexture.mSize.mWidth, pTexture.mSize.mHeight};

			if(pAngle != 0)
			{
				pAngle = D3DX_PI/(180/pAngle);
			}

			D3DXMATRIX mat;
			D3DXVECTOR2 mov((-(cos(pAngle)*pCenter_X-sin(pAngle)*pCenter_Y))+pPoint.mX+pCenter_X, (-(sin(pAngle)*pCenter_X+cos(pAngle)*pCenter_Y))+pPoint.mY+pCenter_Y);

			D3DXMatrixTransformation2D(&mat, NULL, NULL, NULL, NULL, pAngle, &mov);
			mpD3D_Sprite->SetTransform(&mat);
			
			D3DXVECTOR3 Pos(0, 0, 0);
			mpD3D_Sprite->Draw(pTexture.mpTexture, &rc, NULL, &Pos, Common::DX_RGBA(255, 255, 255, pAlpha));

			return true;
		}
		bool KINRenderManager::DrawTexture(Texture& pTexture, const Common::KINPoint& pPoint, float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y, int pAlpha)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || pTexture.mpTexture == NULL)
			{
				return false;
			}

			RECT rc = {0, 0, pTexture.mSize.mWidth, pTexture.mSize.mHeight};

			pCenter_X *= pScaling_Width;
			pCenter_Y *= pScaling_Height;

			D3DXMATRIX mat;
			D3DXVECTOR2 sc(pScaling_Width, pScaling_Height);

			D3DXMatrixTransformation2D(&mat, NULL, NULL, &sc, NULL, 0.f, NULL);
			mpD3D_Sprite->SetTransform(&mat);
			
			D3DXVECTOR3 Pos(0, 0, 0);
			mpD3D_Sprite->Draw(pTexture.mpTexture, &rc, NULL, &Pos, Common::DX_RGBA(255, 255, 255, pAlpha));

			return true;
		}
		bool KINRenderManager::DrawTexture(Texture& pTexture, const Common::KINPoint& pPoint, float pAngle, float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y, int pAlpha)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || pTexture.mpTexture == NULL)
			{
				return false;
			}

			RECT rc = {0, 0, pTexture.mSize.mWidth, pTexture.mSize.mHeight};

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
			mpD3D_Sprite->SetTransform(&mat);
			
			D3DXVECTOR3 Pos(0, 0, 0);
			mpD3D_Sprite->Draw(pTexture.mpTexture, &rc, NULL, &Pos, Common::DX_RGBA(255, 255, 255, pAlpha));

			return true;
		}
		bool KINRenderManager::DrawTexture(Texture& pTexture, const Common::KINPoint& pPoint, const Common::KINRect& pRect, int pAlpha)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || pTexture.mpTexture == NULL)
			{
				return false;
			}

			RECT rc = {pRect.mX, pRect.mY, pRect.mWidth, pRect.mHeight};

			D3DXMATRIX mat;
			D3DXVECTOR2 mov(pPoint.mX, pPoint.mY);
			D3DXMatrixTransformation2D(&mat, NULL, NULL, NULL, NULL, 0.f, &mov);
			mpD3D_Sprite->SetTransform(&mat);
			
			D3DXVECTOR3 Pos(0, 0, 0);
			mpD3D_Sprite->Draw(pTexture.mpTexture, &rc, NULL, &Pos, Common::DX_RGBA(255, 255, 255, pAlpha));

			return true;
		}
		bool KINRenderManager::DrawTexture(Texture& pTexture, const Common::KINPoint& pPoint, const Common::KINRect& pRect, float pAngle, float pCenter_X, float pCenter_Y, int pAlpha)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || pTexture.mpTexture == NULL)
			{
				return false;
			}

			RECT rc = {pRect.mX, pRect.mY, pRect.mWidth, pRect.mHeight};

			if(pAngle != 0)
			{
				pAngle = D3DX_PI/(180/pAngle);
			}

			D3DXMATRIX mat;
			D3DXVECTOR2 mov((-(cos(pAngle)*pCenter_X-sin(pAngle)*pCenter_Y))+pPoint.mX+pCenter_X, (-(sin(pAngle)*pCenter_X+cos(pAngle)*pCenter_Y))+pPoint.mY+pCenter_Y);

			D3DXMatrixTransformation2D(&mat, NULL, NULL, NULL, NULL, pAngle, &mov);
			mpD3D_Sprite->SetTransform(&mat);
			
			D3DXVECTOR3 Pos(0, 0, 0);
			mpD3D_Sprite->Draw(pTexture.mpTexture, &rc, NULL, &Pos, Common::DX_RGBA(255, 255, 255, pAlpha));

			return true;
		}
		bool KINRenderManager::DrawTexture(Texture& pTexture, const Common::KINPoint& pPoint, const Common::KINRect& pRect, float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y, int pAlpha)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || pTexture.mpTexture == NULL)
			{
				return false;
			}

			RECT rc = {pRect.mX, pRect.mY, pRect.mWidth, pRect.mHeight};

			pCenter_X *= pScaling_Width;
			pCenter_Y *= pScaling_Height;

			D3DXMATRIX mat;
			D3DXVECTOR2 sc(pScaling_Width, pScaling_Height);

			D3DXMatrixTransformation2D(&mat, NULL, NULL, &sc, NULL, 0.f, NULL);
			mpD3D_Sprite->SetTransform(&mat);
			
			D3DXVECTOR3 Pos(0, 0, 0);
			mpD3D_Sprite->Draw(pTexture.mpTexture, &rc, NULL, &Pos, Common::DX_RGBA(255, 255, 255, pAlpha));

			return true;
		}
		bool KINRenderManager::DrawTexture(Texture& pTexture, const Common::KINPoint& pPoint, const Common::KINRect& pRect, float pAngle, float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y, int pAlpha)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || pTexture.mpTexture == NULL)
			{
				return false;
			}

			RECT rc = {pRect.mX, pRect.mY, pRect.mWidth, pRect.mHeight};

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
			mpD3D_Sprite->SetTransform(&mat);
			
			D3DXVECTOR3 Pos(0, 0, 0);
			mpD3D_Sprite->Draw(pTexture.mpTexture, &rc, NULL, &Pos, Common::DX_RGBA(255, 255, 255, pAlpha));

			return true;
		}
	}
}