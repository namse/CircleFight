#include "KINRM.h"
#include "KINWM.h"

namespace KIN
{
	namespace Render
	{
		Frame::Frame(Common::KINPoint& pPoint, Texture* pTexture, float pAngle,
						float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y, int pAlpha)
			: mPoint(pPoint), mTexture(pTexture), mAngle(pAngle), mScaling_Width(pScaling_Width),
			  mScaling_Height(pScaling_Height), mCenter_X(pCenter_X), mCenter_Y(pCenter_Y), mAlpha(pAlpha)
		{
		}
		Frame::~Frame(void)
		{
		}

		Animation::Animation(void)
			: mbIsDraw(false)
		{
		}

		Animation::~Animation(void)
		{
		}
		
		bool KINRM::DrawAnimation(Animation& pAnimation, const Common::KINPoint& pPoint, int pAlpha)
		{
			if(mpD3D == NULL || mpD3D_Device == NULL ||
			   mpD3D_Sprite == NULL || pAnimation.mFrame.size() == 0)
			{
				return false;
			}

			if(!pAnimation.mbIsDraw)
			{
				pAnimation.mbIsDraw = true;
				pAnimation.mTimer.Init();
				pAnimation.mfTime = 0;
				pAnimation.mit = pAnimation.mFrame.begin();
			}

			double Time = pAnimation.mTimer.GetTime();
			if(Time - pAnimation.mfTime >= pAnimation.mit->mElapsed)
			{
				pAnimation.mfTime = Time;
				pAnimation.mit++;
				if(pAnimation.mit == pAnimation.mFrame.end())
				{
					pAnimation.mit = pAnimation.mFrame.begin();
				}
			}

			DrawTexture(*(pAnimation.mit->mTexture), pAnimation.mit->mPoint, pAnimation.mit->mAngle, pAnimation.mit->mScaling_Width, pAnimation.mit->mScaling_Height, pAnimation.mit->mCenter_X, pAnimation.mit->mCenter_Y, pAnimation.mit->mAlpha);

			return true;
		}
	}
}