#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <xstring>


HBRUSH hbrush, h_brush[6];
TCHAR const *str = _T("SOLID BRUSH");
TCHAR const *hstr[] = {_T("HS_BDIAGONAL"),_T("HS_BDIAGONAL"), _T("HS_DIAGCROSS"), _T("HS_FDIAGONAL"), _T("HS_HORIZONTAL"), _T("HS_VERTICAL")};

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
	int i;
	int nIndex[] = { HS_BDIAGONAL, HS_CROSS, HS_DIAGCROSS, HS_FDIAGONAL, HS_HORIZONTAL, HS_VERTICAL };

	switch (message)
	{
	case WM_CREATE:
		hbrush = CreateSolidBrush(RGB(255, 255, 0));
		for (i = 0; i < 6; i++)
			h_brush[i] = CreateHatchBrush(nIndex[i], RGB(0, 128, 0));
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SelectObject(hdc, hbrush);
		Ellipse(hdc, 1, 1, 40, 40);
		TextOut(hdc, 50, 11, str, _tcsclen(str));
		for (i = 0; i < 6; i++)
		{
			SelectObject(hdc, h_brush[i]);
			Rectangle(hdc, 1, 41 + 40 * i, 40, 80 + i * 40);
			TextOut(hdc, 50, 51 + i * 40, hstr[i], _tcsclen(hstr[i]));
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hbrush);
		for (i = 0; i < 6; i++) DeleteObject(h_brush[i]);
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}