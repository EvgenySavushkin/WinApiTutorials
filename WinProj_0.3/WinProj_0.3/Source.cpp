#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <xstring>



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
	HDC hdc;
	PAINTSTRUCT ps;
	static int t;
	TCHAR s[10], str[20] = _T("Seconds: ");
	
	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL);
		break;
	case WM_TIMER:
		t++;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
#pragma warning(suppress : 4996)
		_tcscat(str + 9, _itot(t, s, 10));
		TextOut(hdc, 0, 0, (LPSTR)str, _tcsclen((LPSTR)str));
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY: 
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}