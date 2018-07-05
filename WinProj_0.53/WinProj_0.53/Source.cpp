#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <xstring>

#define IDM_EXIT 101
#define ID_CYCLE 102
#define ID_FILE_OPEN 103


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
int APIENTRY _tWinMain(HINSTANCE This, HINSTANCE Prev, LPTSTR cmd, int mode)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wc;

	wc.hInstance = This;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0;
	hWnd = CreateWindow(WinName, _T("First App"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, HWND_DESKTOP, NULL, This, NULL);
	ShowWindow(hWnd, mode);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR str[60], tmp[20];
	int i, sum;
	LARGE_INTEGER freaquency, Start, End;
	static __int64 totalTime;

	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_CYCLE:
			QueryPerformanceFrequency(&freaquency);
			Sleep(0);
			QueryPerformanceCounter(&Start);
			for (i = sum = 0; i < 1000; i++) sum += i;
			QueryPerformanceCounter(&End);
			totalTime = (End.QuadPart - Start.QuadPart) * 1000000 / freaquency.QuadPart;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_EXIT: DestroyWindow(hWnd); break;
		default: return DefWindowProc(hWnd, message, wParam, lParam);
		}
	case WM_CREATE:

		HMENU hMenu, hSubMenu;
		hMenu = CreateMenu();
		hSubMenu = CreatePopupMenu();

		AppendMenu(hSubMenu, MF_STRING, IDM_EXIT, "&Exit");
		AppendMenu(hSubMenu, MF_STRING, ID_CYCLE, "&Cycle");
		AppendMenu(hSubMenu, MF_STRING, ID_FILE_OPEN, "&Open");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

		SetMenu(hWnd, hMenu);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		_tcscpy_s(str, _T("Время работы цикла в мкс: "));
#pragma warning(suppress : 4996)
		_i64tot(totalTime, tmp, 10);
		_tcscat_s(str, tmp);
		TextOut(hdc, 0, 0, str, _tcslen(str));
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}