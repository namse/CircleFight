#include "KINUIM.h"
#include "KINIM.h"

namespace KIN
{
	namespace UserInterface
	{
		KINUIEvent::KINUIEvent(void)
			: mLeftButtonDown(false), mRightButtonDown(false), mMiddleButtonDown(false),
			  mLeftButtonUp(false), mRightButtonUp(false), mMiddleButtonUp(false)
		{
			memset(mKeyCodeDown, 0, 256 * sizeof(bool));
			memset(mKeyCodeUp, 0, 256 * sizeof(bool));
		}
		KINUIEvent::~KINUIEvent(void)
		{
		}



		KINUIItem::KINUIItem(void)
		{
		}
		KINUIItem::~KINUIItem(void)
		{
		}
			
		void KINUIItem::EventHandler(Input::KINIM* pInput)
		{
			for(int i = 0; i < 256; ++i)
			{
				if(mEvent.mKeyCodeDown[i] && pInput->mKeyboard.IsKeyDown(i, 0.5f))
				{
					OnKeyDown(i);
				}
				else if(mEvent.mKeyCodeUp[i] && !pInput->mKeyboard.IsKeyUp(i))
				{
					OnKeyUp(i);
				}
			}
			
			if(mRect.mX <= pInput->mMouse.mPoint.mX && pInput->mMouse.mPoint.mX <= mRect.mX + mRect.mWidth &&
			   mRect.mY <= pInput->mMouse.mPoint.mY && pInput->mMouse.mPoint.mY <= mRect.mY + mRect.mHeight)
			{
				bool Flag = false;

				if(pInput->mMouse.mLeftButton == true && mEvent.mLeftButtonDown)
				{
					if(mEvent.mLeftButtonDownFlag == false)
					{
						// Down
						mEvent.mLeftButtonDownFlag = true;
						Flag = true;
						OnLButtonDown(pInput->mMouse.mPoint);
					}
				}
				else if(mEvent.mLeftButtonUp)
				{
					if(mEvent.mLeftButtonDownFlag == true)
					{
						// Up
						mEvent.mLeftButtonDownFlag = false;
						OnLButtonUp(pInput->mMouse.mPoint);
					}
				}

				if(pInput->mMouse.mRightButton == true && mEvent.mRightButtonDown)
				{
					if(mEvent.mRightButtonDownFlag == false)
					{
						// Down
						mEvent.mRightButtonDownFlag = true;
						Flag = true;
						OnRButtonDown(pInput->mMouse.mPoint);
					}
				}
				else if(mEvent.mRightButtonUp)
				{
					if(mEvent.mRightButtonDownFlag == true)
					{
						// Up
						mEvent.mRightButtonDownFlag = false;
						OnRButtonUp(pInput->mMouse.mPoint);
					}
				}

				if(pInput->mMouse.mMiddleButton == true && mEvent.mMiddleButtonDown)
				{
					if(mEvent.mMiddleButtonDownFlag == false)
					{
						// Down
						mEvent.mMiddleButtonDownFlag = true;
						Flag = true;
						OnMButtonDown(pInput->mMouse.mPoint);
					}
				}
				else if(mEvent.mMiddleButtonUp)
				{
					if(mEvent.mMiddleButtonDownFlag == true)
					{
						// Up
						mEvent.mMiddleButtonDownFlag = false;
						OnMButtonUp(pInput->mMouse.mPoint);
					}
				}

				if(Flag == false)
				{
					OnMouseOver(pInput->mMouse.mPoint);
				}
			}			
		}

		void KINUIItem::OnMouseOver(Common::KINPoint pPoint, void* pData)
		{
		}
		void KINUIItem::OnLButtonDown(Common::KINPoint pPoint, void* pData)
		{
		}
		void KINUIItem::OnLButtonUp(Common::KINPoint pPoint, void* pData)
		{
		}
		void KINUIItem::OnMButtonDown(Common::KINPoint pPoint, void* pData)
		{
		}
		void KINUIItem::OnMButtonUp(Common::KINPoint pPoint, void* pData)
		{
		}
		void KINUIItem::OnRButtonDown(Common::KINPoint pPoint, void* pData)
		{
		}
		void KINUIItem::OnRButtonUp(Common::KINPoint pPoint, void* pData)
		{
		}
		void KINUIItem::OnKeyDown(unsigned char pKeyCode, void* pData)
		{
		}
		void KINUIItem::OnKeyUp(unsigned char pKeyCode, void* pData)
		{
		}
	}
}