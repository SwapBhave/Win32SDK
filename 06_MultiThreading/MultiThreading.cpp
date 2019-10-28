//header files
#include<windows.h>
//call back function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//winmain
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//variable declaration
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("MultiThreading");
	//wndclass structure
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbClsExtra = NULL;
	wndclass.cbWndExtra = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	//register class
	RegisterClassEx(&wndclass);
	//create window
	hwnd = CreateWindow(szAppName, "Threading", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	//show window
	ShowWindow(hwnd, nCmdShow);
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
//call back function defination
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HANDLE hThread1, hThread2;
	DWORD dwID1, dwID2;
	switch (iMsg)
	{
	case WM_CREATE:
		hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, &dwID1);
		if (hThread1 == 0)
		{
			MessageBox(hwnd, "Thread1 Creation failed..!!", "Warning", MB_OK | MB_ICONWARNING);
			DestroyWindow(hwnd);
		}
		hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, &dwID2);
		if (hThread2 == 0)
		{
			MessageBox(hwnd, "Thread2 Creation failed..!!", "Warning", MB_OK | MB_ICONWARNING);
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, "I m Fourth Thread", "Hello", MB_OK);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID param)
{
	HDC hdc;
	int i;
	TCHAR str[255];
	hdc = GetDC((HWND)param);
	for (i = 0; i <= 32767; i++)
	{
		wsprintf(str, TEXT("Thread1 counting is = %d"), i);
		TextOut(hdc, 5, 5, str, strlen(str));
		Sleep(100);
	}
	ReleaseDC((HWND)param, hdc);
	return(0);
}

DWORD WINAPI ThreadProcTwo(LPVOID param)
{
	HDC hdc;
	int i;
	TCHAR str[255];
	hdc = GetDC((HWND)param);
	for (i = 32762; i >= 0; i--)
	{
		wsprintf(str, TEXT("Thread2 counting is = %d"), i);
		TextOut(hdc, 5, 25, str, strlen(str));
		Sleep(100);
	}
	ReleaseDC((HWND)param, hdc);
	return(0);
}