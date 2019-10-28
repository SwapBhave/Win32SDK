#include<windows.h>

#define WIN_WIDTH 800;
#define WIN_HEIGHT 600;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Window Centre using GetSystemMatrics");

	int ScreenWidth, ScreenHeight, ClientWidth, ClientHeight,WidthDifference,HeightDifference;
	ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	WidthDifference = ScreenWidth - WIN_WIDTH;
	HeightDifference = ScreenHeight - WIN_HEIGHT;


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

	//hwnd = CreateWindow(szAppName, TEXT("Window At Centre"), WS_OVERLAPPEDWINDOW, 0, 0,800,600, NULL, NULL, hInstance, NULL);
	hwnd = CreateWindow(szAppName, TEXT("Window At Centre"), WS_OVERLAPPEDWINDOW,(WidthDifference/2),(HeightDifference/2), 800, 600, NULL, NULL, hInstance, NULL);
	UpdateWindow(hwnd);
	ShowWindow(hwnd,iCmdShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN:
		DestroyWindow(hwnd);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}