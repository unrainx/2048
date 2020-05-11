#include "app.hpp"

void log(const char * info) {
	//FILE * fd = fopen("./log.text", "a+");
	//int length = 0;
	//for (int i = 0; info[i] != '\0'; i++) {
	//	length = i + 1;
	//}
	//fwrite(info, sizeof info[0], length, fd);
	//fwrite("\n", sizeof "\n"[0], 1, fd);
	//fclose(fd);
}


int Circle::mode = 0;

LRESULT _stdcall WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static Subject * subject;
	static Circle * quitBtn;
	HWND BeginButton[3];
	HDC hdc;
	PAINTSTRUCT ps;
	//static Map m;
	static RECT rect, block, BottomRect;
	COORD coord;
	static int height, width;
	static int cxClient, cyClient, cxChar, cyChar;
	HBRUSH hBrush;
	static HFONT hFont;
	if (subject != nullptr) {
		subject->notify(hwnd, message, wParam, lParam);
	}
	
	switch (message) {
	case WM_CREATE:
	{
		log("log:\0");
		subject = new Subject;
		quitBtn = new Circle();
		subject->addMember(quitBtn);
		subject->debug();
		quitBtn->render(hwnd);




	}
		

		//BeginButton[0] = CreateWindow(TEXT("Button"), TEXT("Begin"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 60, 50, 100, 30, hwnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		//BeginButton[1] = CreateWindow(TEXT("Button"), TEXT("Save"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 190, 50, 100, 30, hwnd, (HMENU)1, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		//BeginButton[2] = CreateWindow(TEXT("Button"), TEXT("About"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 330, 50, 100, 30, hwnd, (HMENU)2, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		//cxChar = LOWORD(GetDialogBaseUnits());
		//cyChar = HIWORD(GetDialogBaseUnits());
		return 0;
	case WM_SIZE:
		GetWindowRect(hwnd, &rect);
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
	case WM_PAINT:
		HPEN hPen;
		HBRUSH hBrush;
		PAINTSTRUCT ps;
		HDC hdc;

		quitBtn->render(hwnd);

			//hBrush = CreateSolidBrush(RGB(252, 193, 59));
			//SelectObject(hdc, hBrush);
			//hPen = CreatePen(PS_SOLID, 1, RGB(250, 190, 60));
			//SelectObject(hdc, hPen);
			//Ellipse(hdc, 25, 5, 40, 20);
			//hBrush = CreateSolidBrush(RGB(54, 205, 70));
			//SelectObject(hdc, hBrush);
			//hPen = CreatePen(PS_SOLID, 1, RGB(50, 200, 70));
			//SelectObject(hdc, hPen);
			//Ellipse(hdc, 45, 5, 60, 20);
		// AppleCaption(hwnd, hdc, cxClient, cyClient);
		TextOut(hdc, cxClient / 2 - lstrlen(L"Rain") / 2 * cxChar, 5, TEXT("Rain"), lstrlen(TEXT("Rain")));
		/*hBrush = CreateSolidBrush(RGB(187, 171, 158));
		SetRect(&BottomRect, cxClient / 8, cyClient - cxClient, cxClient / 8 * 7, (cyClient - cxClient) + cxClient / 4 * 3);
		FillRect(hdc, &BottomRect, hBrush);
		TextOut(hdc, cxClient / 8, (cyClient - cxClient) + cxClient / 8 * 7, TEXT("TIP:"), lstrlen(TEXT("TIP:")));*/
		EndPaint(hwnd, &ps);
		return 0;
	case WM_LBUTTONDOWN:
		coord.X = LOWORD(lParam);
		coord.Y = HIWORD(lParam);
		if (coord.Y <= 30 && coord.X>20) {
			SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);//通过欺骗DefWindowProc来实现无标题栏win32程序的窗口移动
		}
		return 0;

	case WM_COMMAND:
		/*switch (LOWORD(wParam)) {
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
		SetFocus(hwnd);*/
		return 0;
	case WM_KEYUP:
		/*if (!IsBegin)return 0;
		switch (wParam) {
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
		if (IsFailure(m)) {
			TextOut(hdc, cxClient / 8 * 2, (cyClient - cxClient) + cxClient / 8 * 7, TEXT("Defeat"), lstrlen(TEXT("Defeat")));
		}
		ReleaseDC(hwnd, hdc);*/
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}