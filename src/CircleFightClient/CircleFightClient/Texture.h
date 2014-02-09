#pragma once

#include "KINCommon.h"

namespace KIN
{
	namespace Render
	{
		class Texture
		{
		public:
			LPDIRECT3DTEXTURE9		mpTexture;
			Common::KINSize	mSize;

		public:
			Texture(void);
			~Texture(void);
		};
	}
}