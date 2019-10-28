#include<Windows.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	
//Global Function Declaration

void sw_AllignWindowCentre(HWND,LONG,LONG);

//Global Variable Declaration



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdSLine, int nCmdShow)
{
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("Window at Centre");

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
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("MY Centre Window"), WS_OVERLAPPEDWINDOW, 100, 100,800,600, NULL, NULL, hInstance, NULL);

	UpdateWindow(hwnd);
	ShowWindow(hwnd, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:
		MessageBox(hwnd, "Inside WM_CREATE", "Step Success", MB_OK);
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, "Inside WM_LBUTTONDOWN", "Step Success", MB_OK);
		sw_AllignWindowCentre(hwnd, 800, 600); //sw_AllignWindowCenter(Handle to window,Expected Width,Expected Height)
		break;

	case WM_DESTROY:
		DestroyWindow(hwnd);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}


void sw_AllignWindowCentre(HWND centreHwnd,LONG WindowWidth,LONG WindowHeight)
{
	MessageBox(centreHwnd, "Inside sw_AllignWindowCentre", "Step Success", MB_OK);
	MONITORINFO MonitorInfoStruct;
	LONG MonitorWidth, MonitorHeight,HeightDifference,WidthDifference;
	BOOL bStatus;
	HMONITOR hMonitor;

	MonitorInfoStruct.cbSize = sizeof(MonitorInfoStruct);

	hMonitor = MonitorFromWindow(centreHwnd, MONITOR_DEFAULTTOPRIMARY);
	if (hMonitor == INVALID_HANDLE_VALUE)
	{
		MessageBox(centreHwnd, "Not Valid Monitor Handle", "Step Failed", MB_OK);
	}
	bStatus = GetMonitorInfo(hMonitor, &MonitorInfoStruct);
	if (bStatus == 0)
	{
		MessageBox(centreHwnd, "GetMonitorInfo Failed", "Step Failed", MB_OK);
	}

	MonitorWidth = MonitorInfoStruct.rcMonitor.right - MonitorInfoStruct.rcMonitor.left;
	MonitorHeight = MonitorInfoStruct.rcMonitor.bottom - MonitorInfoStruct.rcMonitor.top;
	HeightDifference = (MonitorHeight - WindowHeight)/2;
	WidthDifference = (MonitorWidth - WindowWidth)/2;


	SetWindowPos(centreHwnd,
		HWND_TOP,
		WidthDifference,
		HeightDifference,
		WindowWidth,
		WindowHeight,
		SWP_NOZORDER | SWP_FRAMECHANGED);
}