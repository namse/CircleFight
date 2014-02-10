#include "KINEngine.h"

int main(void)
{
	// Server's IP, Port
	// KINNetworkManager net("localhost", 9001);
	// Window
	KINWM win(L"������ �̸�", KINRect(0, 0, 800, 600));
	// Render
	KINRenderManager rdr(win);
	// Input
	KINInputManager input(&win);
	// Timer
	KINTimeManager tframe;


	int x=20, y=20;


	while(win.PeekMsg())
	{
		input.Detect();
		{
			if(input.mKeyboard.IsKeyDown(KeyCode::KIN_Left, 0.05f))
			{
				x--;
			} else if(input.mKeyboard.IsKeyDown(KeyCode::KIN_Right, 0.05f))
			{
				x++;
			}
		
			if(input.mKeyboard.IsKeyDown(KeyCode::KIN_Up, 0.05f))
			{
				y--;
			} else if(input.mKeyboard.IsKeyDown(KeyCode::KIN_Down, 0.05f))
			{
				y++;
			}
		}
		

		if(tframe.CheckFrame(60))
		{
			rdr.BeginDrawing();

			rdr.DrawString(L"���� ���", KINPoint(x, y), L"�ؽ�Ʈ�׽�Ʈ", 20, 400, DT_NOCLIP, DX_RGBA(255,255,255,255));

			rdr.EndDrawing();
		}
	}

	return 0;
}