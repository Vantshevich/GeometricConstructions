//"�� �� ��"
#undef UNICODE 
#include <Windows.h>
#include <cstring>
#include <string>
#include <wingdi.h>
#include "CTrapezoid.h"
#include "CBuilder.h"

#define ID_BUTTON1 1212
#define ID_BUTTON2 2000
#define ID_EDIT1 1122
#define ID_EDIT2 2432
#define ID_EDIT3 2324
#define ID_STATIC1 3872
#define ID_MENU1 2222
#define MENU_ABOUT 230
#define MENU_PROGRAM 229
#define EXIT_PROGRAM 228
#define MAXPOINTS 1000
#define MoveTo(hdc, x, y) MoveToEx (hdc, x, y, NULL)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInstance;

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int iCmdShow) {

	PSTR lpszCN = (PSTR)"FirstWindow";

	MSG msg = { 0 };
	HWND hWnd;
	WNDCLASSEX wndClass = { 0 };

	wndClass.cbSize = sizeof(wndClass);
	wndClass.lpszClassName = lpszCN;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndClass);

	hWnd = CreateWindow(lpszCN,
		"Drawing figures",
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		700,
		500,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, hWnd, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

BOOL CreateMenuItem(HMENU hMenu, PSTR str, UINT ulns, UINT uCom, HMENU hSubMenu, bool flag, UINT fType) {
	MENUITEMINFO mii;
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.cch = sizeof(str);
	mii.fState = MFS_ENABLED;
	mii.dwTypeData = str;
	mii.wID = uCom;
	mii.hSubMenu = hSubMenu;
	mii.fType = fType;
	mii.fMask = MIIM_ID | MIIM_STATE | MIIM_SUBMENU | MIIM_TYPE;

	return InsertMenuItem(hMenu, ulns, flag, &mii);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	static HMENU hMainMenu, hFileMenu;
	static CBuilder z(hWnd);
	PAINTSTRUCT  ps;
	HDC          hdc; 
	int          x, y;

	std::string str;
	switch (msg) {
	case WM_CREATE:

		hMainMenu = CreateMenu();
		hFileMenu = CreatePopupMenu();
		CreateMenuItem(hFileMenu, (PSTR)"Exit", 3, EXIT_PROGRAM, NULL, FALSE, MFT_STRING);
		CreateMenuItem(hMainMenu, (PSTR)"Program", 1, MENU_PROGRAM, hFileMenu, FALSE, MFT_STRING);
		CreateMenuItem(hMainMenu, (PSTR)"About", 2, MENU_ABOUT, 0, FALSE, MFT_STRING);
		SetMenu(hWnd, hMainMenu);
		DrawMenuBar(hWnd);
		break;
	case WM_COMMAND:
		switch (wParam) {

		case EXIT_PROGRAM:
			PostQuitMessage(0);
			break;
		case MENU_ABOUT:
			MessageBox(hWnd, "This program was created by Oleg Vancevic 2021", "About", 0);
			break;
		case ID_BUTTON1:
			break;
		case ID_BUTTON2:
			break;
		}
		break;
		case WM_LBUTTONDOWN:
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			if(!z.IsFinished())
				z.OnClick(x, y);
		case WM_MOUSEMOVE: 
			z.OnMove(LOWORD(lParam), HIWORD(lParam));
			return 0;

		case WM_LBUTTONUP: 
			InvalidateRect(hWnd, NULL, FALSE);  
			return 0;

		case WM_PAINT: 
			hdc = BeginPaint(hWnd, &ps); 
			EndPaint(hWnd, &ps); 
			DeleteDC(hdc);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	

	return 0;
}