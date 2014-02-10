#pragma once

#include "KINCommon.h"

namespace KIN
{
	namespace Time
	{
		class KINTimeManager
		{
		private:
			DWORD_PTR mOldmask;
			LARGE_INTEGER mTime;

		public:
			KINTimeManager(void);

			void Init(void);
			double GetTime(void);
			bool CheckFrame(unsigned int pFPS = 60);
		};
	}
}