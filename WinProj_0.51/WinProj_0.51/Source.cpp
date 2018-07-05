#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <xstring>

#define IDM_EXIT 101
#define ID_FILE_DELETE 102
#define ID_FILE_OPEN 103

TCHAR *pStr;

DWORD WINAPI MyThread(LPVOID param)
{
	pStr = (TCHAR*)param;
	return 0;
}

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
	TCHAR const *str = _T("Theread worked");

	switch (message)
	{

	case WM_CREATE:

		HMENU hMenu, hSubMenu;
		hMenu = CreateMenu();
		hSubMenu = CreatePopupMenu();

		AppendMenu(hSubMenu, MF_STRING, IDM_EXIT, "&Exit");
		AppendMenu(hSubMenu, MF_STRING, ID_FILE_DELETE, "&Delete");
		AppendMenu(hSubMenu, MF_STRING, ID_FILE_OPEN, "&Open");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

		SetMenu(hWnd, hMenu);

		CreateThread(NULL, 0, MyThread, (LPVOID)str, 0, NULL);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_EXIT: DestroyWindow(hWnd);break;
		default: return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 0, 0, pStr, _tcslen(pStr));
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}