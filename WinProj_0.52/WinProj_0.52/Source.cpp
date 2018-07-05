#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <xstring>
#include <process.h>

unsigned __stdcall MyThread(void * param)
{
	for (int i = 0; i < 10000000; i++);
	return 0;
}

#define IDM_EXIT 101
#define ID_THREAD 102
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
	HANDLE hThread;
	LARGE_INTEGER Create, Exit, kernel, user;
	static __int64 kernelTime, userTime, totalTime;
	TCHAR str[256];
	RECT rt;

	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_THREAD:
			hThread = (HANDLE)_beginthreadex(NULL, 0, MyThread, NULL, 0, NULL);
			WaitForSingleObject(hThread, INFINITE);
			GetThreadTimes(hThread, (FILETIME*)&Create.u, (FILETIME*)&Exit.u, (FILETIME*)&kernel.u, (FILETIME*)&user.u);
			CloseHandle(hThread);
			kernelTime = kernel.QuadPart;
			userTime = user.QuadPart;
			totalTime = Exit.QuadPart - Create.QuadPart;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default: return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		GetClientRect(hWnd, &rt);
		hdc = BeginPaint(hWnd, &ps);
		_stprintf_s(str, _T("kernelTime = %I64d\nuserTime = %I64d\ntotalTime= %I64d"), kernelTime, userTime, totalTime);
		DrawText(hdc, str, _tcslen(str), &rt, DT_LEFT);
		EndPaint(hWnd, &ps);
		break;
	case WM_CREATE:

		HMENU hMenu, hSubMenu;
		hMenu = CreateMenu();
		hSubMenu = CreatePopupMenu();

		AppendMenu(hSubMenu, MF_STRING, IDM_EXIT, "&Exit");
		AppendMenu(hSubMenu, MF_STRING, ID_THREAD, "&Thread");
		AppendMenu(hSubMenu, MF_STRING, ID_FILE_OPEN, "&Open");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

		SetMenu(hWnd, hMenu);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}