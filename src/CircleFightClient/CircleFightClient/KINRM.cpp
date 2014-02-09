#include "KINRM.h"
#include "KINWM.h"

namespace KIN
{
	namespace Render
	{
		KINRM::KINRM(void)
		: mWM(NULL), mpD3D(NULL), mpD3D_Device(NULL), mpD3D_Sprite(NULL), mpD3D_Font_Sprite(NULL), mIsWindowMode(true)
		{
			::ZeroMemory(&mD3D_Present_Parameters, sizeof(mD3D_Present_Parameters));
			::ZeroMemory(&mD3D_DisplayMode, sizeof(D3DDISPLAYMODE));
			::ZeroMemory(&mWindowPlacement, sizeof(WINDOWPLACEMENT));
		}

		KINRM::KINRM(const Window::KINWM& pWM, const bool& pIsWindowMode)
		: mWM(NULL), mpD3D(NULL), mpD3D_Device(NULL), mpD3D_Sprite(NULL), mpD3D_Font_Sprite(NULL), mIsWindowMode(true)
		{
			::ZeroMemory(&mD3D_Present_Parameters, sizeof(mD3D_Present_Parameters));
			::ZeroMemory(&mD3D_DisplayMode, sizeof(D3DDISPLAYMODE));
			::ZeroMemory(&mWindowPlacement, sizeof(WINDOWPLACEMENT));

			Init(pWM, pIsWindowMode);
		}

		KINRM::~KINRM(void)
		{
			Destroy();
		}

		bool KINRM::Init_Present_Parameters(void)
		{
			::ZeroMemory(&mD3D_Present_Parameters, sizeof(mD3D_Present_Parameters));

			D3DFORMAT AdapterFormat = (mIsWindowMode == true) ? mD3D_DisplayMode.Format : D3DFMT_X8R8G8B8;

			if(SUCCEEDED(mpD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, AdapterFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24S8)))
			{
				mD3D_Present_Parameters.AutoDepthStencilFormat = D3DFMT_D24S8;
			}
			else if(SUCCEEDED(mpD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, AdapterFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24X8)))
			{
				mD3D_Present_Parameters.AutoDepthStencilFormat = D3DFMT_D24X8;
			}
			else if(SUCCEEDED(mpD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, AdapterFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D16)))
			{
				mD3D_Present_Parameters.AutoDepthStencilFormat = D3DFMT_D16;
			}
			else
			{
				printf("I can't find depth valid format\n");
				return false;
			}
	
			mD3D_Present_Parameters.BackBufferWidth            = mWM->mClientSize.mWidth;
			mD3D_Present_Parameters.BackBufferHeight           = mWM->mClientSize.mHeight;
			mD3D_Present_Parameters.BackBufferFormat           = AdapterFormat;
			mD3D_Present_Parameters.BackBufferCount            = 1;
			mD3D_Present_Parameters.Flags					  = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
			mD3D_Present_Parameters.MultiSampleType            = D3DMULTISAMPLE_NONE;
			mD3D_Present_Parameters.MultiSampleQuality         = 0;
			mD3D_Present_Parameters.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
			mD3D_Present_Parameters.hDeviceWindow              = mWM->GetHWND();
			mD3D_Present_Parameters.Windowed                   = mIsWindowMode;
			mD3D_Present_Parameters.EnableAutoDepthStencil     = TRUE; 
			mD3D_Present_Parameters.FullScreen_RefreshRateInHz = (mIsWindowMode) ? 0 : mD3D_DisplayMode.RefreshRate;
			mD3D_Present_Parameters.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

			return true;
		}

		bool KINRM::Init(const Window::KINWM &pWM, const bool &pIsWindowMode)
		{
			Destroy();

			if(mWM) delete mWM;
			mWM = new Window::KINWM();
			*mWM = pWM;
			mIsWindowMode = pIsWindowMode;

			mpD3D = Direct3DCreate9(D3D_SDK_VERSION);

			if(mpD3D == NULL)
			{
				printf("mpD3D 실패\n");
				return false;
			}

			mpD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mD3D_DisplayMode);

			D3DCAPS9 Caps;

			if(FAILED(mpD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &Caps)))
			{
				printf("mpD3D Cap 실패\n");
				return false;
			}

			DWORD VertexProcessing = 0;
			if(Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
			{
				VertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;

				if(Caps.DevCaps & D3DDEVCAPS_PUREDEVICE)
				{
					VertexProcessing |= D3DCREATE_PUREDEVICE;
				}
			}
			else
			{
				VertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
			}

			if(Init_Present_Parameters() == false)
			{
				if(mpD3D != NULL)
				{
					mpD3D->Release();
					mpD3D = NULL;
				}

				printf("mpD3D PP 실패\n");
				return false;
			}

			HRESULT hResult = 0;

			hResult = mpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, mWM->GetHWND(), VertexProcessing |= D3DCREATE_MULTITHREADED,
										 &mD3D_Present_Parameters, &mpD3D_Device);
			if(FAILED(hResult))
			{
				if(mpD3D != NULL)
				{
					mpD3D->Release();
					mpD3D = NULL;
				}

				printf("mpD3D Device 실패 : %d", (unsigned int)hResult);
				return false;
			}
			
			D3DXCreateSprite(mpD3D_Device, &mpD3D_Sprite);
			D3DXCreateSprite(mpD3D_Device, &mpD3D_Font_Sprite);

			return true;
		}

		void KINRM::Destroy(void)
		{
			if(mpD3D)
			{
				mpD3D->Release();
				mpD3D = NULL;
			}
	
			if(mpD3D_Device)
			{
				mpD3D_Device->Release();
				mpD3D_Device = NULL;
			}
	
			if(mpD3D_Sprite)
			{
				mpD3D_Sprite->Release();
				mpD3D_Sprite = NULL;
			}
	
			if(mpD3D_Font_Sprite)
			{
				mpD3D_Font_Sprite->Release();
				mpD3D_Font_Sprite = NULL;
			}
	
			::ZeroMemory(&mD3D_Present_Parameters, sizeof(mD3D_Present_Parameters));
			::ZeroMemory(&mD3D_DisplayMode, sizeof(D3DDISPLAYMODE));
			::ZeroMemory(&mWindowPlacement, sizeof(WINDOWPLACEMENT));
		}

		bool KINRM::ResetDevice(void)
		{
			if(Init_Present_Parameters())
			{
				if(mpD3D_Sprite != NULL)
					mpD3D_Sprite->Release();
				mpD3D_Sprite = NULL;
				if(mpD3D_Font_Sprite != NULL)
					mpD3D_Font_Sprite->Release();
				mpD3D_Font_Sprite = NULL;
				if(!FAILED(mpD3D_Device->Reset(&mD3D_Present_Parameters)))
				{
					D3DXCreateSprite(mpD3D_Device, &mpD3D_Sprite);
					D3DXCreateSprite(mpD3D_Device, &mpD3D_Font_Sprite);
					return true;
				}
				else
				{
					return false;
				}
			}

			return false;
		}

		void KINRM::BeginDrawing(unsigned int pColor)
		{
			HRESULT hr = mpD3D_Device->TestCooperativeLevel();

			if(FAILED(hr))
			{
				switch(hr)
				{
				case D3DERR_DEVICELOST:
					{
						::Sleep(500);

						break;
					}
				case D3DERR_DEVICENOTRESET:
					{
						if(ResetDevice() == false)
						{
							printf("디바이스 재생성 실패\n");
						}

						break;
					}
				}
			}

			if(mpD3D_Device == NULL)
			{
				return;
			}

			if(FAILED(mpD3D_Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, pColor, 1.0f, 0)))
			{
				return;
			}

			mpD3D_Device->BeginScene();

			mpD3D_Sprite->Begin(D3DXSPRITE_ALPHABLEND);
		}

		void KINRM::EndDrawing(void)
		{
			mpD3D_Sprite->End();

			mpD3D_Device->EndScene();

			mpD3D_Device->Present(NULL, NULL, NULL, NULL);

			// 여기에 디바이스 소실 부분 추가
		}

		bool KINRM::Capture(const std::wstring& pPath, const Common::KINRect& pRect)
		{
			IDirect3DSurface9* pBackBuffer;
			HRESULT hr = mpD3D_Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);

			if(hr == S_OK)
			{
				RECT RC = { pRect.mX, pRect.mY, pRect.mX + pRect.mWidth, pRect.mY + pRect.mHeight };
				if(pRect.mWidth == 0 && pRect.mHeight == 0)
				{
					RC.left = 0;
					RC.right = mWM->mClientSize.mWidth;
					RC.top = 0;
					RC.bottom = mWM->mClientSize.mHeight;
				}
				D3DXSaveSurfaceToFileW(pPath.c_str(), D3DXIFF_PNG, pBackBuffer, NULL, &RC);
				pBackBuffer->Release();

				return true;
			}

			return false;
		}
	}
}