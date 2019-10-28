#include<Windows.h>
#include<stdio.h>

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
	wndclass.hCursor = NULL;
	wndclass.hIcon = NULL;
	wndclass.hIconSm = NULL;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	//class register
	RegisterClassEx(&wndclass);
	//create window
	hwnd = CreateWindow(szAppName, TEXT("MyApp"), WS_MINIMIZE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
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
	INPUT input;
	INPUT input1;
	int i = 0;

	switch (iMsg)
	{
	case WM_CREATE:
		//Move to Start
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.dx = 20 * (65536 / GetSystemMetrics(SM_CXSCREEN));
		input.mi.dy = 750 * (65536 / GetSystemMetrics(SM_CYSCREEN));
		input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(input));
		Sleep(1000);

		//Move to Power
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.dx = 20 * (65536 / GetSystemMetrics(SM_CXSCREEN));
		input.mi.dy = 700 * (65536 / GetSystemMetrics(SM_CYSCREEN));
		input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(input));
		Sleep(1000);

		//Move to ShutDown and click
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.dx = 20 * (65536 / GetSystemMetrics(SM_CXSCREEN));
		input.mi.dy = 650 * (65536 / GetSystemMetrics(SM_CYSCREEN));
		input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(input));
		Sleep(1000);

		DestroyWindow(hwnd);

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	//DefWindowProc
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
