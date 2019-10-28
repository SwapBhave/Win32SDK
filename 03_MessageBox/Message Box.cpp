#include<Windows.h>

//call back function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = NULL;
	wndclass.hIcon = NULL;
	wndclass.hIconSm = NULL;
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
	while (GetMessage(&msg, NULL,0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}
//call back function defination
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR text[]= TEXT("Hello World..!!!!");
	RECT rc;
	TCHAR str[]=TEXT("Press OK to Continue");

	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SetTextColor(hdc, RGB(0, 255, 0));
		SetBkMode(hdc, TRANSPARENT);
		DrawText(hdc, text, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		break;
	case WM_CREATE:
		wsprintf(str,"Press OK");
		MessageBox(hwnd, str, "Welcome", MB_OK| MB_ICONQUESTION);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, "Left button is pressed", "Mouse Button", MB_OK| MB_ICONINFORMATION);
		break;
	case WM_KEYDOWN:
	{
		int msgboxID;
		switch (wParam)
		{
		case 'Q':
			msgboxID=MessageBox(hwnd, "Do you want to quit", "Quit", MB_OKCANCEL| MB_ICONINFORMATION);
			switch (msgboxID)
			{
			case IDCANCEL:
				break;
			case IDOK:
				DestroyWindow(hwnd);
				break;
			}
			break;
		case 'A':
			MessageBox(hwnd, "A is pressed", "Key down", MB_OK| MB_ICONINFORMATION);
			break;
		}
	}
		break;
	case WM_SIZE:
	{
		switch (wParam)
		{
		case SIZE_MAXIMIZED:
			MessageBox(hwnd, "Maximizing Window", "MAXIMIZE", MB_OK | MB_ICONSTOP);
			break;
		case SIZE_MINIMIZED:
			MessageBox(hwnd, "Minimizing Window", "MINIMIZE", MB_OK | MB_ICONSTOP);
			break;
		}
	}
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}