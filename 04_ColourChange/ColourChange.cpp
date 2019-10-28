//Header file
#include<Windows.h>
//call back function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//win main function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int iCmdShow)
{
	// declaration
	WNDCLASSEX wndclass;
	MSG msg;
	TCHAR szAppName[]= TEXT("ColourChange");
	HWND hwnd;
	// class parameters declaration
	wndclass.cbClsExtra = NULL;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.cbWndExtra = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = NULL;
	wndclass.hIcon = NULL;
	wndclass.hIconSm = NULL;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc=WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	//register class
	RegisterClassEx(&wndclass);
	//create windows 
	hwnd = CreateWindow(szAppName, TEXT("ColourChange"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	//show window
	ShowWindow(hwnd, iCmdShow);
	//update window
	UpdateWindow(hwnd);
	//get message
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//translate and dispatch message
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//return wparam and end main function
	return((int)msg.wParam);
	
}

//call back function defination
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR name[] = TEXT("Hello World!!!");
	RECT rc;
	//switch case
	switch (iMsg)
	{

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
	{
		HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
		HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0,255));
		HBRUSH yellowBrush = CreateSolidBrush(RGB(255, 255, 0));
		HBRUSH magentaBrush = CreateSolidBrush(RGB(255, 0, 255));
		HBRUSH cyanBrush = CreateSolidBrush(RGB(0,255, 255));
		HBRUSH greyBrush = CreateSolidBrush(RGB(128, 128, 128));
		HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
		switch (wParam)
		{
		case 'R':
			SetClassLong(hwnd, GCLP_HBRBACKGROUND, (LONG)redBrush);
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'G':
			SetClassLong(hwnd, GCLP_HBRBACKGROUND, (LONG)greenBrush);
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'B':
			SetClassLong(hwnd, GCLP_HBRBACKGROUND, (LONG)blueBrush);
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'Y':
			SetClassLong(hwnd, GCLP_HBRBACKGROUND, (LONG)yellowBrush);
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'M':
			SetClassLong(hwnd, GCLP_HBRBACKGROUND, (LONG)magentaBrush);
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'C':
			SetClassLong(hwnd, GCLP_HBRBACKGROUND, (LONG)cyanBrush);
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case 'K':
			SetClassLong(hwnd, GCLP_HBRBACKGROUND, (LONG)blackBrush);
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		default:
			SetClassLong(hwnd, GCLP_HBRBACKGROUND, (LONG)greyBrush);
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
	}
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SetTextColor(hdc, RGB(255, 0, 0));
		SetBkMode(hdc, TRANSPARENT);
		DrawText(hdc, name, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		EndPaint(hwnd, &ps);
		break;
	}
	//return DefWindowProc
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));	
}