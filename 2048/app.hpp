#ifndef __APP_H__

#define __APP_H__

#define IDI_ICON3 105

#include <vector>
#include <windows.h>
#include<TCHAR.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
LRESULT _stdcall WinProc(HWND, UINT, WPARAM, LPARAM);

void log(const char * info);

class App {
public:
	App(HINSTANCE _hInstance, int _iCmdShow) :
		hInstance(_hInstance),
		iCmdShow(_iCmdShow) {

		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc = WinProc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hIcon = LoadIcon(hInstance, LPCWSTR(IDI_ICON3));
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndclass.lpszMenuName = NULL;
		wndclass.lpszClassName = szAppName;
		wndclass.hInstance = hInstance;
		if (!RegisterClass(&wndclass)) {
			MessageBox(NULL, TEXT("This program requirs WindowsNT!"), szAppName, MB_OK);
			abort();
		}
		hwnd = CreateWindowEx(WS_EX_CLIENTEDGE| WS_EX_ACCEPTFILES| WS_THICKFRAME, // WS_EX_LAYERED Í¸Ã÷ÑùÊ½
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
		SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 50, /*LWA_ALPHA |*/ LWA_COLORKEY);

		ShowWindow(hwnd, iCmdShow);
		UpdateWindow(hwnd);

	}

	unsigned run() {

		while (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return msg.wParam;
	}

	
	
	wchar_t * szAppName = L"Rain";
	HWND hwnd;
	WNDCLASS wndclass;
	MSG msg;
	HINSTANCE hInstance;
	int iCmdShow;


};

class ObserverInterface {
public:
	virtual void update(HWND hwnd, int message, unsigned wParam, unsigned lParam) = 0;
};

class Observer : public ObserverInterface {
public:
	Observer(const std::string _name):
		name(_name) {
	}

	virtual void update(HWND hwnd, int message, unsigned wParam, unsigned lParam) override {
		std::cout << name << message << "already update.\n";
	}

private:
	std::string name;
};


class SubjectInterface {
public:

	virtual void addMember(ObserverInterface * observer) = 0;
	virtual void removeMember(ObserverInterface * observer) = 0;
	virtual void notify(HWND hwnd, const int message, const unsigned wParam, const unsigned lParam) = 0;
};


class Subject : public SubjectInterface {
public:
	virtual void addMember(ObserverInterface * observer) override {
		members.push_back(observer);
	}
	virtual void removeMember(ObserverInterface * observer) override {
		for (auto p = members.cbegin(); p != members.cend(); p++) {
			members.erase(p);
		}
	}
	virtual void notify(HWND hwnd, const int message, const unsigned wParam, const unsigned lParam) override {
		for (auto m: members) {
			m->update(hwnd, message, wParam, lParam);
			log("notify internal 1");
		}
		log("notify: member count:");
		debug();
	}
	void debug() {
		std::string s = std::to_string(members.size());
		log(s.c_str());
	}

private:
	std::vector<ObserverInterface*> members = {};
};



class Circle : public ObserverInterface {
	
	
public:


	virtual void update(HWND hwnd, int message, unsigned wParam, unsigned lParam) override {
		coord.X = LOWORD(lParam);
		coord.Y = HIWORD(lParam);

		if (message == WM_MOUSEMOVE && intersection()) {
			global_mode = 1;
			InvalidateRect(hwnd, NULL, true);
		} else if (message == WM_LBUTTONDOWN && intersection()) {
			SendMessage(hwnd, WM_DESTROY, wParam, lParam);
		} else {
			mode = 0;
		}
	}


	void render(HWND hwnd) {
		HPEN hPen;
		HBRUSH hBrush;
		PAINTSTRUCT ps;
		HDC hdc;
		#define COLOR RGB(0, 0, 0)
		if (global_mode == 1) {
			hdc = BeginPaint(hwnd, &ps);
			hBrush = CreateSolidBrush(COLOR);
			SelectObject(hdc, hBrush);
			hPen = CreatePen(PS_SOLID, 1, COLOR);
			SelectObject(hdc, hPen);
			Ellipse(hdc, 5, 5, 20, 20);
			EndPaint(hwnd, &ps);
		} else {
			hdc = BeginPaint(hwnd, &ps);
			hBrush = CreateSolidBrush(RGB(250, 92, 89));
			SelectObject(hdc, hBrush);
			hPen = CreatePen(PS_SOLID, 1, RGB(240, 90, 90));
			SelectObject(hdc, hPen);
			Ellipse(hdc, 5, 5, 20, 20);
			EndPaint(hwnd, &ps);
		}
	}
	

private:
	COORD coord = { 0, 0 };
	typedef struct _position {
		int left = 5;
		int top = 5;
		int right = 20;
		int bottom = 20;
	} position;

	enum Mode {
		normal = 0,
		trap = 1
	};

	static int mode;

	int mark = 0;

	bool intersection() {
		int x = coord.X;
		int y = coord.Y;
		if (x <= 20 && x >= 5 && y <= 20 && y >= 5) {
			return true;
		} else {
			return false;
		}
	}
};






#endif // !__APP_H__
