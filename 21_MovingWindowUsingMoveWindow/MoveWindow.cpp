#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL sw_RepositionWindow(HWND, LONG,LONG);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("My program for WindowMoving");

	wndclass.cbClsExtra = NULL;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.cbWndExtra = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName=NULL;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	
	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("Window Moving using MoveWindow"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	UpdateWindow(hwnd);
	ShowWindow(hwnd, iCmdShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bStatus;

	switch (iMsg)
	{
	case WM_CREATE:
	bStatus = sw_RepositionWindow(hwnd, 800, 600);
	if (bStatus == FALSE)
	{
		MessageBox(hwnd, "sw_RepositionWinodw Failed : SW_CENTRE", "Step Failed", MB_OK);
	}
	AnimateWindow(hwnd, 2000, AW_CENTER);
		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);

		break;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		case 'C':
			MessageBox(hwnd, "Inside WM_KEYDIWN:C", "Step Status", MB_OK);
			bStatus = sw_RepositionWindow(hwnd, 800, 600);
			if (bStatus == FALSE)
			{
				MessageBox(hwnd, "sw_RepositionWinodw Failed : SW_CENTRE", "Step Failed", MB_OK);
			}
			break;
		}
	}
	break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

BOOL sw_RepositionWindow(HWND swHwnd, LONG Width, LONG Height)
{
	BOOL bStatus;

	MONITORINFO MonitorInfoStruct;
	MonitorInfoStruct.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(MonitorFromWindow(swHwnd,MONITORINFOF_PRIMARY), &MonitorInfoStruct);

	LONG MonitorWidth,MonitorHeight;
	LONG HeightDiff, WidthDiff;

	MonitorWidth = MonitorInfoStruct.rcMonitor.right - MonitorInfoStruct.rcMonitor.left;
	MonitorHeight = MonitorInfoStruct.rcMonitor.bottom - MonitorInfoStruct.rcMonitor.top;
	HeightDiff = (MonitorHeight - Height)/2;
	WidthDiff = (MonitorWidth - Width) / 2;
	
	bStatus=MoveWindow(swHwnd, WidthDiff, HeightDiff, Width, Height, TRUE);
	if (bStatus == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
