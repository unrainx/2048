/*2017年3月9日20:34:51*/
/* 2048.c _v1.0_ */

#include "app.hpp"

//Queue queue;
//void AppleCaption(HWND hwnd, HDC hdc, int cxClient, int cyClient);
//void DrawMap(HDC hdc, Map m, int cxClient, int cyClient);

int main(int argc, char ** argv) {

	return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	auto app = App(hInstance, iCmdShow);
	app.run();

	char ** a = nullptr;
	return main(2, a);
}

//void AppleCaption(HWND hwnd,HDC hdc,int cxClient,int cyClient)
//{
//	HBRUSH hBrush;
//	HPEN hPen;
//	RECT block;
//
//	SetRect(&block, 0, 0, cxClient, 25);
//	hBrush = CreateSolidBrush(RGB(246, 246, 246));
//	FillRect(hdc, &block, hBrush);
//	hBrush = CreateSolidBrush(RGB(250, 92, 89));
//	SelectObject(hdc, hBrush);
//	hPen = CreatePen(PS_SOLID, 1, RGB(240, 90, 90));
//	SelectObject(hdc, hPen);
//	Ellipse(hdc, 5, 5, 20, 20);
//	hBrush = CreateSolidBrush(RGB(252, 193, 59));
//	SelectObject(hdc, hBrush);
//	hPen = CreatePen(PS_SOLID, 1, RGB(250, 190, 60));
//	SelectObject(hdc, hPen);
//	Ellipse(hdc, 25, 5, 40, 20);
//	hBrush = CreateSolidBrush(RGB(54, 205, 70));
//	SelectObject(hdc, hBrush);
//	hPen = CreatePen(PS_SOLID, 1, RGB(50, 200, 70));
//	SelectObject(hdc, hPen);
//	Ellipse(hdc, 45, 5, 60, 20);
//
//}
//void DrawMap(HDC hdc,Map m,int cxClient,int cyClient)
//{
//	wchar_t cBuffer[100];
//	int xLeft=100, yLeft=cyClient-cxClient+40;
//	int distance = (cxClient - 20) / 25;
//	RECT rect;
//	HBRUSH hBrush;
//	hBrush = CreateSolidBrush(RGB(207, 191, 178));
//	HFONT hFont;
//	hFont = CreateFont(20, 10, 0, 0, FW_HEAVY, 0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS,
//		CLIP_DEFAULT_PRECIS,
//		DEFAULT_QUALITY,
//		DEFAULT_PITCH | FF_DONTCARE,
//		(TCHAR*)"黑体");
//	SelectObject(hdc, hFont);
//	SetTextColor(hdc, RGB(116, 106, 90));
//	SetBkMode(hdc, TRANSPARENT);	
//	for (int x = 0; x < SIZE; x++)
//	{
//		for (int y = 0; y < SIZE; y++)
//		{
//			SetRect(&rect, xLeft, yLeft, xLeft + 60, yLeft + 60);
//			FillRect(hdc, &rect, hBrush);
//			if (m.map[x][y] != 0)
//			{
//				wsprintf(cBuffer, L"%d", m.map[x][y]);
//				DrawText(hdc, cBuffer, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
//			}
//			xLeft = xLeft + distance + 60;
//		}
//		 yLeft = yLeft + distance + 60;
//		 xLeft = 100;
//	}
//	/*int max = GetInfo(m);
//	wsprintf(cBuffer, L"%d",max);
//	TextOut(hdc, cxClient / 8*2, (cyClient - cxClient) + cxClient / 8 * 7 , cBuffer, lstrlen(cBuffer));*/
//}











//2017年3月19日14:12:28  Rain 2048 _v1.0_.