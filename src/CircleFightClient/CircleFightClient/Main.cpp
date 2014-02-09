#include "KINEngine.h"

int main(void)
{
	KINWM win(L"������ �̸�", KINRect(0, 0, 800, 600));
	KINRM rdr(win);
	KINIM input(&win);
	KINTM tframe;

	while(win.PeekMsg())
	{
		input.Detect();

		if(tframe.CheckFrame(60))
		{
			rdr.BeginDrawing();

			rdr.DrawString(L"���� ���", KINPoint(20, 20), L"�ؽ�Ʈ�׽�Ʈ", 20, 400, DT_NOCLIP, DX_RGBA(255,255,255,255));

			rdr.EndDrawing();
		}
	}

	return 0;
}