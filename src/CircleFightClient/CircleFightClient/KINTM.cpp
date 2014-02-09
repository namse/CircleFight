#include "KINTM.h"

namespace KIN
{
	namespace Time
	{
		KINTM::KINTM(void)
		{
			Init();
		}

		void KINTM::Init(void)
		{
			mOldmask = SetThreadAffinityMask(::GetCurrentThread(), 1);
			QueryPerformanceCounter(&mTime);
		}
		
		double KINTM::GetTime(void)
		{
			LARGE_INTEGER performance_frequency, t_time;
			QueryPerformanceFrequency(&performance_frequency);
			QueryPerformanceCounter(&t_time);  
			SetThreadAffinityMask(::GetCurrentThread(), mOldmask);

			return ((double)(t_time.QuadPart - mTime.QuadPart)/performance_frequency.QuadPart);
		}

		bool KINTM::CheckFrame(unsigned int pFPS)
		{
			static double elapsed = 0.f, elapsed2 = 0.f;
			double nFPS = 1.0f/(double)pFPS;
			double nTime = GetTime();

			if(nTime - elapsed + elapsed2 >= nFPS)
			{
				elapsed2 = nTime - elapsed - nFPS;
				if(elapsed2 >= nFPS) elapsed2 = 0;
				elapsed = nTime;
				return true;
			}

			return false;
		}
	}
}