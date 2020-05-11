/*
 * copyright (c) unrain
 * 2017-3-9
 * 2048.c
*/

#include<windows.h>
#include<TCHAR.h>
#include"2048.h"
#include<stdio.h>
#include"resource.h"
//Queue queue;
void AppleCaption(HWND hwnd, HDC hdc, int cxClient, int cyClient);
void DrawMap(HDC hdc, Map m, int cxClient, int cyClient);
LRESULT _stdcall WinProc(HWND,UINT,WPARAM,LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	TCHAR szAppName[] = TEXT("2048");
	HWND hwnd;
	WNDCLASS wndclass;
	MSG msg;	
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WinProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(hInstance, (LPCWSTR)(IDI_ICON3));
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hInstance = hInstance;
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requirs WindowsNT!"), szAppName, MB_OK);
		return -1;
	}
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, // WS_EX_LAYERED 透明样式
		szAppName,				//window class name
		TEXT("2048"),			//window caption
		WS_POPUP,				//window style
		600,//CW_USEDEFAULT,			//initial x position
		300,//CW_USEDEFAULT,			//initial y position
		500,//CW_USEDEFAULT,			//initial x size
		650,//CW_USEDEFAULT,		//initial y size
		NULL,					//parent window handle
		NULL,					//window menu handle
		hInstance,				//program instance handle
		NULL					//creation parameters
	);
	SetLayeredWindowAttributes(hwnd, RGB(0,0,0), 50, /*LWA_ALPHA |*/ LWA_COLORKEY);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LRESULT _stdcall WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static bool IsBegin = false;
	HWND BeginButton[3];
	HDC hdc;
	PAINTSTRUCT ps;
	static Map m;
	static RECT rect,block,BottomRect;
	COORD coord;
	static int height, width;
	static int cxClient, cyClient,cxChar,cyChar;
	HBRUSH hBrush;
	static HFONT hFont;
	switch (message)
	{
	case WM_CREATE:
		BeginButton[0] = CreateWindow(TEXT("Button"), TEXT("Begin"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 60, 50, 100, 30, hwnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		BeginButton[1] = CreateWindow(TEXT("Button"), TEXT("Save"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 190, 50, 100, 30, hwnd, (HMENU)1, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		BeginButton[2] = CreateWindow(TEXT("Button"), TEXT("About"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,330, 50, 100, 30, hwnd, (HMENU)2, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());
		return 0;
	case WM_SIZE:
		GetWindowRect(hwnd, &rect);
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		AppleCaption(hwnd, hdc, cxClient, cyClient);
		TextOut(hdc, cxClient / 2 - lstrlen(TEXT("2048")) / 2 * cxChar, 5, TEXT("2048"), lstrlen(TEXT("2048")));
		hBrush = CreateSolidBrush(RGB(187, 171, 158));
		SetRect(&BottomRect, cxClient / 8, cyClient - cxClient, cxClient / 8 * 7, (cyClient - cxClient) + cxClient / 4 * 3);
		FillRect(hdc, &BottomRect, hBrush);
		TextOut(hdc, cxClient / 8, (cyClient - cxClient) + cxClient / 8 * 7, TEXT("TIP:"), lstrlen(TEXT("TIP:")));
		EndPaint(hwnd, &ps);
		return 0;
	case WM_LBUTTONDOWN:
		coord.X = LOWORD(lParam);
		coord.Y = HIWORD(lParam);
		if (coord.X <= 20 && coord.Y <= 25)
		{
			SendMessage(hwnd, WM_DESTROY, wParam, lParam);
		}
		if (coord.Y <= 30&&coord.X>20)
		{
			SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);//通过欺骗DefWindowProc来实现无标题栏win32程序的窗口移动
		}
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case 0:
				hdc = GetDC(hwnd);
				IsBegin = true;
				m = InitialMap();
				DrawMap(hdc, m, cxClient, cyClient);
				ReleaseDC(hwnd, hdc);
				break;
			case 1:
				Save(m);
				break;
			case 2:
				MessageBox(hwnd, TEXT("                        2048\nPlease press keys of direction to play.\n                   2017©Rain"), TEXT("About"), MB_OK);
				break;
		}
		SetFocus(hwnd);
		return 0;
	case WM_KEYUP:
		if (!IsBegin)return 0;
		switch (wParam)
		{
		case VK_UP:
			TopMove(&m);			
			break;
		case VK_DOWN:
			BottomMove(&m);
			break;
		case VK_LEFT:
			LeftMove(&m);
			break;
		case VK_RIGHT:
			RightMove(&m);
			break;
		}
		hdc = GetDC(hwnd);
		DrawMap(hdc, m, cxClient, cyClient);
		if(IsFailure(m))
		{
			TextOut(hdc, cxClient / 8*2, (cyClient - cxClient) + cxClient / 8 * 7, TEXT("Defeat"), lstrlen(TEXT("Defeat")));
		}
		ReleaseDC(hwnd, hdc);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
void AppleCaption(HWND hwnd,HDC hdc,int cxClient,int cyClient)
{
	HBRUSH hBrush;
	HPEN hPen;
	RECT block;

	SetRect(&block, 0, 0, cxClient, 25);
	hBrush = CreateSolidBrush(RGB(246, 246, 246));
	FillRect(hdc, &block, hBrush);
	hBrush = CreateSolidBrush(RGB(250, 92, 89));
	SelectObject(hdc, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(240, 90, 90));
	SelectObject(hdc, hPen);
	Ellipse(hdc, 5, 5, 20, 20);
	hBrush = CreateSolidBrush(RGB(252, 193, 59));
	SelectObject(hdc, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(250, 190, 60));
	SelectObject(hdc, hPen);
	Ellipse(hdc, 25, 5, 40, 20);
	hBrush = CreateSolidBrush(RGB(54, 205, 70));
	SelectObject(hdc, hBrush);
	hPen = CreatePen(PS_SOLID, 1, RGB(50, 200, 70));
	SelectObject(hdc, hPen);
	Ellipse(hdc, 45, 5, 60, 20);

}
void DrawMap(HDC hdc,Map m,int cxClient,int cyClient)
{
	wchar_t cBuffer[100];
	int xLeft=100, yLeft=cyClient-cxClient+40;
	int distance = (cxClient - 20) / 25;
	RECT rect;
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(RGB(207, 191, 178));
	HFONT hFont;
	hFont = CreateFont(20, 10, 0, 0, FW_HEAVY, 0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		(TCHAR*)"黑体");
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(116, 106, 90));
	SetBkMode(hdc, TRANSPARENT);	
	for (int x = 0; x < SIZE; x++)
	{
		for (int y = 0; y < SIZE; y++)
		{
			SetRect(&rect, xLeft, yLeft, xLeft + 60, yLeft + 60);
			FillRect(hdc, &rect, hBrush);
			if (m.map[x][y] != 0)
			{
				wsprintf(cBuffer, L"%d", m.map[x][y]);
				DrawText(hdc, cBuffer, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			}
			xLeft = xLeft + distance + 60;
		}
		 yLeft = yLeft + distance + 60;
		 xLeft = 100;
	}
}

//2017年3月19日14:12:28  Rain 2048 _v1.0_.