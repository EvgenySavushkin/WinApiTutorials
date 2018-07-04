#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <xstring>

TCHAR const *text = _T("Text for displaying in window");


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
	TEXTMETRIC tm;
	TCHAR str[256];
	RECT rt;
	SIZE size;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkColor(hdc, RGB(255, 255, 0));
		SetTextColor(hdc, RGB(0, 0, 128));
		TextOut(hdc, 0, 0, text, _tcsclen(text));
		SetBkMode(hdc, TRANSPARENT);
		SelectObject(hdc, GetStockObject(ANSI_VAR_FONT));
		GetTextMetrics(hdc, &tm);

		_stprintf_s(str, _T("tmHeight = %d\ntmInternalLeading = %d\ntmExternalLeading = %d\ntmAscent = %d\ntmDescent = %d\n"), tm.tmHeight, tm.tmInternalLeading, tm.tmExternalLeading, tm.tmAscent, tm.tmDescent);
		SetRect(&rt, 0, 20, 150, 100);
		DrawText(hdc, str, _tcslen(str), &rt, DT_LEFT);
		GetTextExtentPoint32(hdc, text, _tcsclen(text), &size);
		_stprintf_s(str, _T("Ширина строки = %d\nВысота строки = %d"), size.cx, size.cy);
		SetRect(&rt, 0, 100, 150, 150);
		DrawText(hdc, str, _tcslen(str), &rt, DT_LEFT);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}