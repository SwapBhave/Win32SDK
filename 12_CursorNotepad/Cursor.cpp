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
		//Move to search
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.dx = 95 * (65536 / GetSystemMetrics(SM_CXSCREEN));
		input.mi.dy = 750 * (65536 / GetSystemMetrics(SM_CYSCREEN));
		input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(input));
		Sleep(500);
		//Type N for notepad search
		input1.type = INPUT_KEYBOARD;
		input1.ki.wScan = 0;
		input1.ki.time = 0;
		input1.ki.dwExtraInfo = 0;
		input1.ki.wVk = 0x4E;
		input1.ki.dwFlags = 0;
		SendInput(2, &input1, sizeof(input1));
		Sleep(500);
		//goto notepad and press left key
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.dx = 100 * (65536 / GetSystemMetrics(SM_CXSCREEN));
		input.mi.dy = 210 * (65536 / GetSystemMetrics(SM_CYSCREEN));
		input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(input));
		Sleep(500);
		//Goto Note pad
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.dx = 750 * (65536 / GetSystemMetrics(SM_CXSCREEN));
		input.mi.dy = 300 * (65536 / GetSystemMetrics(SM_CYSCREEN));
		input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(input));
		Sleep(500);

		//Type G 
		input1.type = INPUT_KEYBOARD;
		input1.ki.wScan = 0;
		input1.ki.time = 0;
		input1.ki.dwExtraInfo = 0;
		input1.ki.wVk = 0x47;
		input1.ki.dwFlags = 0;
		SendInput(2, &input1, sizeof(input1));
		Sleep(75);

		//Type O twice
		for (i = 0; i < 2; i++)
		{
			input1.type = INPUT_KEYBOARD;
			input1.ki.wScan = 0;
			input1.ki.time = 0;
			input1.ki.dwExtraInfo = 0;
			input1.ki.wVk = 0x4F;
			input1.ki.dwFlags = 0;
			SendInput(2, &input1, sizeof(input1));
			Sleep(75);
		}
		//Type D for notepad search
		input1.type = INPUT_KEYBOARD;
		input1.ki.wScan = 0;
		input1.ki.time = 0;
		input1.ki.dwExtraInfo = 0;
		input1.ki.wVk = 0x44;
		input1.ki.dwFlags = 0;
		SendInput(2, &input1, sizeof(input1));
		Sleep(75);
		//Type space 
		input1.type = INPUT_KEYBOARD;
		input1.ki.wScan = 0;
		input1.ki.time = 0;
		input1.ki.dwExtraInfo = 0;
		input1.ki.wVk = VK_SPACE;
		input1.ki.dwFlags = 0;
		SendInput(2, &input1, sizeof(input1));
		Sleep(75);
		//Type B 
		input1.type = INPUT_KEYBOARD;
		input1.ki.wScan = 0;
		input1.ki.time = 0;
		input1.ki.dwExtraInfo = 0;
		input1.ki.wVk = 0x42;
		input1.ki.dwFlags = 0;
		SendInput(2, &input1, sizeof(input1));
		Sleep(75);
		//Type Y 
		input1.type = INPUT_KEYBOARD;
		input1.ki.wScan = 0;
		input1.ki.time = 0;
		input1.ki.dwExtraInfo = 0;
		input1.ki.wVk = 0x59;
		input1.ki.dwFlags = 0;
		SendInput(2, &input1, sizeof(input1));
		Sleep(75);
		//Type E 
		input1.type = INPUT_KEYBOARD;
		input1.ki.wScan = 0;
		input1.ki.time = 0;
		input1.ki.dwExtraInfo = 0;
		input1.ki.wVk = 0x45;
		input1.ki.dwFlags = 0;
		SendInput(2, &input1, sizeof(input1));
		Sleep(1500);
		//Close Notepad
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.dx = 1100 * (65536 / GetSystemMetrics(SM_CXSCREEN));
		input.mi.dy = 150 * (65536 / GetSystemMetrics(SM_CYSCREEN));
		input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
		SendInput(1, &input, sizeof(input));
		Sleep(550);
		//Click on dont save
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.dx = 710 * (65536 / GetSystemMetrics(SM_CXSCREEN));
		input.mi.dy = 370 * (65536 / GetSystemMetrics(SM_CYSCREEN));
		input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE|MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;;
		SendInput(1, &input, sizeof(input));
		Sleep(550);
		DestroyWindow(hwnd);

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	//DefWindowProc
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
