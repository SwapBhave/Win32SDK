//header file
#include<Windows.h>
#include"window.h"
//call back function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//winmain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{//variable and structure declaration
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("Icon_Display");
	HWND hwnd;
	MSG msg;
	//class defination
	wndclass.cbClsExtra = NULL;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = NULL;
	wndclass.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE("MYICON"));
	wndclass.hIconSm =LoadIcon(hInstance,TEXT("MYICON"));
	wndclass.hInstance = hInstance; 
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	//class registration
	RegisterClassEx(&wndclass);
	//create window
	hwnd = CreateWindow(szAppName, "Icon_Display", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	//show window
	ShowWindow(hwnd, nCmdShow);
	//update window
	UpdateWindow(hwnd);
	// message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//return wparam
	return((int)msg.wParam);
}
//wndproc defination
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	int MessageID;
	//switch case
	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
                 
	}
	//return DefWindowProc
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
