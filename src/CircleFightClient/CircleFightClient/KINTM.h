#pragma once

#include "KINCommon.h"

namespace KIN
{
	namespace Time
	{
		class KINTM
		{
		private:
			DWORD_PTR mOldmask;
			LARGE_INTEGER mTime;

		public:
			KINTM(void);

			void Init(void);
			double GetTime(void);
			bool CheckFrame(unsigned int pFPS = 60);
		};
	}
}