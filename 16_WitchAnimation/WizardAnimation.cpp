#include<Windows.h>
#include"wizard.h"
//#pragma winmm.lib

//call back function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI Sound(LPVOID);
DWORD WINAPI Cloud(LPVOID);
//main funciton
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declaration
	HWND hwnd;
	MSG msg;
	TCHAR szAappName[] = TEXT("MyText");
	WNDCLASSEX wndclass;
	//class structure
	wndclass.cbClsExtra = NULL;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = NULL;
	//wndclass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(128,128, 128));
	wndclass.hbrBackground = ((HBRUSH)GetStockObject(BLACK_BRUSH));
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAappName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	//class registration
	RegisterClassEx(&wndclass);
	//create window
	hwnd = CreateWindow(szAappName, TEXT("MyText"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	//update window
	UpdateWindow(hwnd);
	//show window
	ShowWindow(hwnd, iCmdShow);
	//Message loop
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
	HPEN hWhitePen = (HPEN)CreatePen(PS_SOLID, PS_SOLID, RGB(255, 255, 255));
	HDC hdc,hdcB;
	PAINTSTRUCT ps;
	static HBITMAP hBitMap;
	RECT rc;
	BITMAP bmp;
	HINSTANCE hInstance;
	HBRUSH hWhiteBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH hBlackBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	//int width, height;
	static HANDLE hSound;
	DWORD dwSound;

	switch (iMsg)
	{
	case WM_CREATE:
		//int j;
		hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
		hBitMap = LoadBitmap(hInstance, MAKEINTRESOURCE(MY_BITMAP));
		hSound = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Sound, (LPVOID)hwnd, 0, &dwSound);
		if (hSound == 0)
		{
			MessageBox(hwnd, "Sound Creation failed..!!", "Warning", MB_OK | MB_ICONWARNING);
			DestroyWindow(hwnd);
		}
		/*for (j = 0; j < 500; j++)
		{
			PlaySound("C:\\abc.wav", NULL, SND_FILENAME);
		}
		*/
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		int i;
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		hdcB = CreateCompatibleDC(hdc);
		//width = GetDeviceCaps(hdc, HORZSIZE);
		//height = GetDeviceCaps(hdc, VERTRES);
		//Create Moon
		SelectObject(hdc, hWhiteBrush);
		Ellipse(hdc, rc.left/2.5, rc.top+70, rc.right/2.5, rc.bottom-70);
		Sleep(2000);
		SelectObject(hdcB, hBitMap);
		GetObject(hBitMap, sizeof(bmp), &bmp);
		//StretchBlt(hdc,rc.left,rc.right,rc.right-rc.left,rc.bottom-rc.top,hdcB,100,100,bmp.bmWidth,bmp.bmHeight,SRCCOPY);
		//saglyat varti left side la
		//BitBlt(hdc, 650, 0,(rc.right-rc.left),(rc.bottom-rc.top), hdcB, 0, 0, SRCCOPY);
		//saglyat khalti left side la
		//BitBlt(hdc, 650, 500, (rc.right - rc.left), (rc.bottom - rc.top), hdcB, 0, 0, SRCCOPY);
		//saglyat khalti right side la
		//BitBlt(hdc, 1100, 500, (rc.right - rc.left), (rc.bottom - rc.top), hdcB, 0, 0, SRCCOPY);
		//PlaySound("C:\\abc.wav", NULL, SND_FILENAME);
		Sleep(5000);
		for (i =0; i < 900; i++)
		{
			Sleep(10);
			//BitBlt(hdc, 1100-i, 500-i, (rc.right - rc.left), (rc.bottom - rc.top), hdcB, 0, 0, SRCCOPY);
			BitBlt(hdc, 1150 - i, 650 - i, (rc.right - rc.left), (rc.bottom - rc.top), hdcB, 0, 0, SRCCOPY);
		}

		DeleteDC(hdcB);
		ReleaseDC(hwnd, hdc);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI Sound(LPVOID param)
{
	
	//PlaySound("C:\\abc.wav", NULL, SND_FILENAME);
	Sleep(8000);
	PlaySound("C:\\MyVisualStudio2017Projects\\WizardAnimation\\abc.wav", NULL, SND_FILENAME);
	return (0);
}


