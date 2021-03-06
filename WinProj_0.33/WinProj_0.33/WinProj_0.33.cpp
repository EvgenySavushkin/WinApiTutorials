// WinProj_0.33.cpp: Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "WinProj_0.33.h"
#include <commctrl.h>

#define MAX_LOADSTRING 100

// Глобальные переменные:
static int spin, track, progress;
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
INT_PTR CALLBACK Dialog1(HWND, UINT, WPARAM, LPARAM);
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINPROJ033, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINPROJ033));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINPROJ033));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINPROJ033);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR str[256];
	RECT rt;
    switch (message)
    {
	case WM_CREATE:
		InitCommonControls();
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
			case ID_COMMCTRL:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog1);
				break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
		SetRect(&rt, 0, 0, 100, 100);
            hdc = BeginPaint(hWnd, &ps);
			_stprintf_s(str, _T("spin\t= %d\ntrack\t= %d\nprogress= %d"), spin, track, progress);
			DrawText(hdc, str, _tcslen(str), &rt, DT_LEFT | DT_EXPANDTABS);
			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Dialog1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int t, track;
	static HWND hSpin, hBuddy, hTrack, hProgress;
	switch (message)
	{
	case WM_INITDIALOG:
		track = ::track;
		SetDlgItemInt(hDlg, IDC_TR1, track, 0);
		hTrack = GetDlgItem(hDlg, IDC_SLIDER1);
		SendMessage(hTrack, TBM_SETRANGE, 0, 100 << 16);
		SendMessage(hTrack, TBM_SETPOS, TRUE, track);
		hSpin = GetDlgItem(hDlg, IDC_SPIN1);
		hBuddy = GetDlgItem(hDlg, IDC_SP1);
		SendMessage(hSpin, UDM_SETBUDDY, (WPARAM)hBuddy, 0);
		SendMessage(hSpin, UDM_SETRANGE, 0, 100);
		SendMessage(hSpin, UDM_SETPOS, 0, spin);
		hProgress = GetDlgItem(hDlg, IDC_PROGRESS1);
		SendMessage(hProgress, PBM_SETRANGE, 0, 100 << 16);
		SendMessage(hProgress, PBM_SETSTEP, 1, 0);
		SendMessage(hProgress, PBM_SETPOS, t, 0);
		SetTimer(hDlg, 1, 100, NULL);
		return TRUE;
	case WM_TIMER:
		if (++t > 99) t = 0;
		SendMessage(hProgress, PBM_SETPOS, t, 0);
		return TRUE;
	case WM_HSCROLL:
		track = LOWORD(SendMessage(hTrack, TBM_GETPOS, 0, 0));
		SetDlgItemInt(hDlg, IDC_TR1, track, 0);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			progress = t;
			::track = track;
			spin = SendMessage(hSpin, UDM_GETPOS, 0, 0);
			InvalidateRect(GetParent(hDlg), NULL, 1);
		case IDCANCEL:
			KillTimer(hDlg, 1);
			EndDialog(hDlg, 0);
			return TRUE;
		default: return FALSE;
		}
	}
	return FALSE;
}