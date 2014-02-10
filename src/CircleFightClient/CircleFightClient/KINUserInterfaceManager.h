#pragma once

#include "KINCommon.h"
#include "Texture.h"

namespace KIN
{
	namespace Input
	{
		class KINInputManager;
	}

	namespace UserInterface
	{
		typedef enum
		{
			NORMAL,
			DOWN,
			OVER,
			SELECT,

			MAX,
		} UIStatus;

		class KINUIEvent
		{
		public:
			bool mKeyCodeDown[256];
			bool mKeyCodeUp[256];
			bool mLeftButtonDown;
			bool mRightButtonDown;
			bool mMiddleButtonDown;
			bool mLeftButtonUp;
			bool mRightButtonUp;
			bool mMiddleButtonUp;
			bool mLeftButtonDownFlag;
			bool mRightButtonDownFlag;
			bool mMiddleButtonDownFlag;

		public:
			KINUIEvent(void);
			~KINUIEvent(void);
		};

		class KINUIItem
		{
		public:
			wstring mName;

			bool mbShow;
			bool mbMove;
			Common::KINRect mRectCaption;
			Common::KINRect mRect;

			UIStatus mUIStatus;
			Render::Texture* mTexture[UIStatus::MAX];

			KINUIEvent mEvent;

		public:
			KINUIItem(void);
			~KINUIItem(void);
			
		public:
			virtual void EventHandler(Input::KINInputManager* pInput);
		private:
			virtual void OnMouseOver(Common::KINPoint pPoint, void* pData=NULL);
			virtual void OnLButtonDown(Common::KINPoint pPoint, void* pData=NULL);
			virtual void OnLButtonUp(Common::KINPoint pPoint, void* pData=NULL);
			virtual void OnMButtonDown(Common::KINPoint pPoint, void* pData=NULL);
			virtual void OnMButtonUp(Common::KINPoint pPoint, void* pData=NULL);
			virtual void OnRButtonDown(Common::KINPoint pPoint, void* pData=NULL);
			virtual void OnRButtonUp(Common::KINPoint pPoint, void* pData=NULL);
			virtual void OnKeyDown(unsigned char pKeyCode, void* pData=NULL);
			virtual void OnKeyUp(unsigned char pKeyCode, void* pData=NULL);
		};

		class KINUserInterfaceManager
		{
		private:
			list<KINUIItem*> mListUIItem;

		public:
			KINUserInterfaceManager(void);
			~KINUserInterfaceManager(void);
		};
	}
}