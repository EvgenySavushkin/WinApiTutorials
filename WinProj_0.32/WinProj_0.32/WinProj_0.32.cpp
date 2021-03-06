// WinProj_0.32.cpp: Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "WinProj_0.32.h"
#include <tchar.h>

#define MAX_LOADSTRING 100

// Глобальные переменные:
static int radio, check1, check2, scrlh, scrlv, lIndex, cIndex;
int *val[] = {&radio,&check1,&check2,&scrlh,&scrlv, &lIndex, &cIndex};
TCHAR const *combo[100] = { _T("a"),_T("b"),_T("c") };
TCHAR  const *list[100] = { _T("string 1"), _T("string 2"), _T("string 3") };
TCHAR const *ctrl = _T("Элементы управления:");
TCHAR const *str_control[] = { _T("Radio Button"),_T("Check Button 1"),_T("Check Button 2"),_T("HScroll Pos"),_T("VScroll Pos"),_T("List Box Index"),_T("Combo Box Index") };
const int HNUM = 10, VNUM = 100;
const int List_size = 3, Combo_size = 3;
const int INTERVAL = 20;
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
    LoadStringW(hInstance, IDC_WINPROJ032, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINPROJ032));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINPROJ032));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINPROJ032);
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
	int i;
    switch (message)
    {

		
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
			case ID_STDDIALOG:
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

			hdc = BeginPaint(hWnd, &ps);
			TextOut(hdc, 0, 0, ctrl, _tcslen(ctrl));
			for (i = 0; i < 7;)
			{
				_stprintf_s(str, _T("%s = %d"), str_control[i], *val[i]);
				TextOut(hdc, 0, ++i*INTERVAL, str, _tcslen(str));
			}
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

INT_PTR CALLBACK Dialog1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int radio, check1, check2, scrlh, scrlv;
	static HWND hScroll, vScroll, hWndList, hWndComboBox;
	int i;
	switch (message)
	{
	case WM_INITDIALOG:
		radio = ::radio;
		CheckRadioButton(hDlg, IDC_RADIO3, IDC_RADIO5, IDC_RADIO3 + radio);
		check1 = ::check1;
		SendDlgItemMessage(hDlg, IDC_CHECK1, BM_SETCHECK, check1, 0);
		check2 = ::check2;
		SendDlgItemMessage(hDlg, IDC_CHECK2, BM_SETCHECK, check2, 0);
		scrlh = ::scrlh;
		SetDlgItemInt(hDlg, IDC_HSCR, scrlh, 0);
		hScroll = GetDlgItem(hDlg, IDC_SCROLLBAR1);
		SetScrollRange(hScroll, SB_CTL, 0, HNUM, FALSE);
		SetScrollPos(hScroll, SB_CTL, scrlh, TRUE);
		scrlv = ::scrlv;
		SetDlgItemInt(hDlg, IDC_VSCR, scrlv, 0);
		vScroll = GetDlgItem(hDlg, IDC_SCROLLBAR2);
		SetScrollRange(vScroll, SB_CTL, 0, VNUM, FALSE);
		SetScrollPos(vScroll, SB_CTL, scrlv, TRUE);
		hWndList = GetDlgItem(hDlg, IDC_LIST1);
		for ( i = 0; i < List_size; i++) SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM)list[i]);
		SendMessage(hWndList, LB_SETCURSEL, lIndex, 0);
		hWndComboBox = GetDlgItem(hDlg, IDC_COMBO1);
		for (i = 0; i < Combo_size; i++) SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)combo[i]);
		SendMessage(hWndComboBox, CB_SETCURSEL, cIndex, 0);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			lIndex = SendMessage(hWndList, LB_GETCURSEL, 0, 0);
			cIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
			::radio = radio;
			::check1 = check1;
			::check2 = check2;
			::scrlh = scrlh;
			::scrlv = scrlv;
			InvalidateRect(GetParent(hDlg), NULL, 1);
		case IDCANCEL: return EndDialog(hDlg, 0);
		case IDC_CHECK1: check1 = ~check1;
			SendDlgItemMessage(hDlg, IDC_CHECK1, BM_SETCHECK, check1, 0);
			return TRUE;
		case IDC_CHECK2: check2 = ~check2;
			SendDlgItemMessage(hDlg, IDC_CHECK2, BM_SETCHECK, check2, 0);
			return TRUE;
		case IDC_RADIO3: radio = 0; break;
		case IDC_RADIO4: radio = 1; break;
		case IDC_RADIO5: radio = 2; break;
		}
		CheckRadioButton(hDlg, IDC_RADIO3, IDC_RADIO5, IDC_RADIO3 + radio);
		return TRUE;
	case WM_HSCROLL:
		switch (LOWORD(wParam))
		{
		case SB_LINELEFT: scrlh--; break;
		case SB_LINERIGHT: scrlh++; break;
		case SB_PAGELEFT: scrlh -= HNUM / 2; break;
		case SB_PAGERIGHT: scrlh += HNUM / 2; break;
		case SB_THUMBPOSITION: scrlh = HIWORD(wParam); break;
		}
		scrlh = max(0, min(scrlh, HNUM));
		if (scrlh != GetScrollPos(hScroll, SB_CTL))
		{
			SetScrollPos(hScroll, SB_CTL, scrlh, TRUE);
			SetDlgItemInt(hDlg, IDC_HSCR, scrlh, 0);
		}
		return TRUE;
	case WM_VSCROLL:
		switch (LOWORD(wParam))
		{
		case SB_LINEUP: scrlv--; break;
		case SB_LINEDOWN: scrlv++; break;
		case SB_PAGEUP: scrlv -= VNUM / 10; break;
		case SB_PAGEDOWN: scrlv += VNUM / 10; break;
		case SB_THUMBPOSITION: scrlv = HIWORD(wParam);break;
		}
		scrlv = max(0, min(scrlv, VNUM));
		if (scrlv != GetScrollPos(vScroll, SB_CTL))
		{
			SetScrollPos(vScroll, SB_CTL, scrlv, TRUE);
			SetDlgItemInt(hDlg, IDC_VSCR, scrlv, 0);
		}
		return TRUE;
	default: return FALSE;
	}
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
