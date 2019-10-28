#include<Windows.h>
#include"MyResource.h"

//declare callback function
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//winmain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//Variable declaration
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("MyApp");
	//class structure
	wndclass.cbClsExtra = NULL;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(hInstance,IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	//class register
	RegisterClassEx(&wndclass);
	//create window
	hwnd = CreateWindow(szAppName, TEXT("MyApp"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	//show window
	ShowWindow(hwnd, iCmdShow);
	//update window
	UpdateWindow(hwnd);
	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}
//Callback Defination
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInstance;
	static HBITMAP hBitMap;
	PAINTSTRUCT ps;
	HDC hdc,hdcB;
	BITMAP bmp;
	switch (iMsg)
	{
	case WM_CREATE:
		hInstance=(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
		hBitMap=LoadBitmap(hInstance,MAKEINTRESOURCE(MY_BITMAP));
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hdcB = CreateCompatibleDC(hdc);
		SelectObject(hdcB,hBitMap);
		GetObject(hBitMap,sizeof(bmp),&bmp);
		BitBlt(hdc,0,0,bmp.bmWidth,bmp.bmHeight,hdcB,0,0,SRCCOPY);
		DeleteDC(hdc);
		DeleteDC(hdcB);
		EndPaint(hwnd,&ps);
		break;
	case WM_DESTROY:
		DeleteObject(hBitMap);
		PostQuitMessage(0);
		break;
	}
	//DefWindowProc
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
