#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <xstring>

TCHAR const *text = _T("Наклонный текст");


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
	HFONT oldFont, newFont;
	int Escapement,i;
	static int sx, sy,k;

	switch (message)
	{
	case WM_CREATE:
		 i = MessageBox(hWnd, _T("Do you want display italic text?"), _T("Text format"), MB_YESNO | MB_ICONQUESTION);
		 k = (i == IDYES) ? 1 : 0;
		break;
	case WM_SIZE:
		sx = LOWORD(lParam) / 2;
		sy = HIWORD(lParam) / 2;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (Escapement = 0; Escapement < 3600; Escapement += 200)
		{
			newFont = CreateFont(20,0,Escapement, 0,700,k,0,0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
			oldFont = (HFONT)SelectObject(hdc, newFont);
			TextOut(hdc, sx, sy, text, _tcsclen(text));
			SelectObject(hdc, oldFont);
			DeleteObject(newFont);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}