#pragma once

#include "KINCommon.h"
#include "KINTimeManager.h"
#include "Texture.h"

namespace KIN
{
	namespace Render
	{
		class Frame
		{
		public:
			Common::KINPoint mPoint;
			Texture* mTexture;
			float mAngle;
			float mScaling_Width;
			float mScaling_Height;
			float mCenter_X;
			float mCenter_Y;
			int mAlpha;

			double mElapsed;

		public:
			Frame(Common::KINPoint& pPoint, Texture* pTexture, float pAngle,
						float pScaling_Width, float pScaling_Height, float pCenter_X, float pCenter_Y, int pAlpha=255);
			~Frame(void);
		};
		class Animation
		{
		public:
			bool mbIsDraw;
			double mfTime;
			Time::KINTimeManager mTimer;
			vector<Frame> mFrame;
			vector<Frame> ::iterator mit;

		public:
			Animation(void);
			~Animation(void);
		};
	}
}
	