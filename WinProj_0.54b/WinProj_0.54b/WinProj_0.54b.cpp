// WinProj_0.54b.cpp: Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "WinProj_0.54b.h"
#include <process.h>
#include <commctrl.h>
#define MAX_LOADSTRING 100

HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];
HANDLE hSemaphore;
INT_PTR CALLBACK Dialog1(HWND, UINT, WPARAM, LPARAM);

HWND SetElement(HWND hDlg, HDC& mem, WORD IdBitmap, WORD IdProgress)
{
	HBITMAP hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IdBitmap));
	HDC hdc = GetDC(hDlg);
	mem = CreateCompatibleDC(hdc);
	ReleaseDC(hDlg, hdc);
	SelectObject(mem, hBitmap);
	HWND handle = GetDlgItem(hDlg, IdProgress);
	SendMessage(handle, PBM_SETRANGE, 0, 30 << 16);
	SendMessage(handle, PBM_SETSTEP, 1, 0);
	SendMessage(handle, PBM_SETPOS, 0, 0);
	return handle;
}


unsigned __stdcall MyThread1(void* param)
{
	HWND hWnd = (HWND)param;
	HDC hdc, mem;
	int t = 0;
	HWND hProgress = SetElement(hWnd, mem, NULL, IDC_PROGRESS1);
	while (1)
	{
		WaitForSingleObject(hSemaphore, INFINITE);
		Sleep(500);
		hdc = GetDC(hWnd);
		BitBlt(hdc, 320, 25, 25, 50, mem, 0, 0, SRCCOPY);
		ReleaseDC(hWnd, hdc);
		if (++t > 30) t = 0;
		SendMessage(hProgress, PBM_SETPOS, t, 0);
		ReleaseSemaphore(hSemaphore, 1, NULL);
	}
	return 0;
}

unsigned __stdcall MyThread2(void* param)
{
	HWND hWnd = (HWND)param;
	HDC hdc, mem;
	int t = 0;
	HWND hProgress = SetElement(hWnd, mem, NULL, IDC_PROGRESS2);
	while (1)
	{
		WaitForSingleObject(hSemaphore, INFINITE);
		Sleep(500);
		hdc = GetDC(hWnd);
		BitBlt(hdc, 320, 25, 25, 50, mem, 0, 0, SRCCOPY);
		ReleaseDC(hWnd, hdc);
		if (++t > 30) t = 0;
		SendMessage(hProgress, PBM_SETPOS, t, 0);
		ReleaseSemaphore(hSemaphore, 1, NULL);
	}
	return 0;
}
	
// Глобальные переменные:
        // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
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
    LoadStringW(hInstance, IDC_WINPROJ054B, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINPROJ054B));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINPROJ054B));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINPROJ054B);
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
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
			case ID_SEMAPHORE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog1);
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
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
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
	static HANDLE hThread1, hThread2;
	switch (message)
	{
	case WM_INITDIALOG:
		InitCommonControls();
		hSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
		hThread1 = (HANDLE)_beginthreadex(NULL, 0, MyThread1, hDlg, 0, NULL);
		hThread2 = (HANDLE)_beginthreadex(NULL, 0, MyThread2, hDlg, 0, NULL);
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			TerminateThread(hThread1, 0);
			TerminateThread(hThread2, 0);
			CloseHandle(hThread1);
			CloseHandle(hThread2);
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}