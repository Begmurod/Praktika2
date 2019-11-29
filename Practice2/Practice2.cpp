// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("WinAPI Practice");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("WinAPI Practice Title");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance;

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 500,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR text[] = _T("Саидмуродов Бегмурод");
	HBRUSH tbrush;

	hdc = BeginPaint(hWnd, &ps);

	POINT pentagon[6];
	pentagon[0].x = 400; pentagon[0].y = 0;
	pentagon[1].x = 470; pentagon[1].y = 50;
	pentagon[2].x = 440; pentagon[2].y = 120;
	pentagon[3].x = 360; pentagon[3].y = 120;
	pentagon[4].x = 330; pentagon[4].y = 50;
	pentagon[5].x = 400; pentagon[5].y = 0;

	POINT polygon[13] = { pentagon[0].x, pentagon[0].y, pentagon[1].x, pentagon[1].y, 
		pentagon[2].x, pentagon[2].y, pentagon[3].x, pentagon[3].y, 
		pentagon[4].x, pentagon[4].y, pentagon[5].x, pentagon[5].y };

	const BYTE Actions[6] = { PT_MOVETO, PT_LINETO, PT_LINETO, PT_LINETO, PT_LINETO, PT_LINETO };

	tbrush = CreateSolidBrush(RGB(0, 0, 255));

	SelectObject(hdc, tbrush);
	Polygon(hdc, polygon, 5);
	PolyDraw(hdc, pentagon, Actions, 6);

	TextOut(hdc, 0, 430, text, _tcslen(text));
	EndPaint(hWnd, &ps);

	return DefWindowProc(hWnd, message, wParam, lParam);
}