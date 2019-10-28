#include<Windows.h>

//declare callback function
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//winmain

BOOL sw_FullScreenResolution(HWND,int, int, int);

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
	hwnd = CreateWindow(szAppName, TEXT("MyApp"), WS_OVERLAPPEDWINDOW,0,0,800,600, NULL, NULL, hInstance, NULL);
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
	BOOL bStatus;
	//LONG lStatus;

	switch (iMsg)
	{
	case WM_CREATE:
		break;

	case WM_LBUTTONDOWN:

		bStatus = sw_FullScreenResolution(hwnd, 800, 600, 32);
		if (bStatus == FALSE)
		{
			MessageBox(hwnd, "Failed to call sw_FullScreenResolution", "Step Failed", MB_OK);
		}
		break;

	case WM_RBUTTONDOWN:
		DestroyWindow(hwnd);
		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	//DefWindowProc
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}


BOOL sw_FullScreenResolution(HWND resHwnd,int Width, int Height, int BitPerPixel)
{
	static BOOL bResolutionIsDefault = FALSE;
	static DEVMODE CurDevMode,PrevDevMode;
	PrevDevMode.dmSize = sizeof(PrevDevMode);
	CurDevMode.dmSize = sizeof(CurDevMode);
	BOOL bStatus;
	LONG lStatus;
	static DWORD dwStyle;

	if (bResolutionIsDefault == FALSE)
	{
		dwStyle = GetWindowLong(resHwnd, GWL_STYLE);
		SetWindowLong(resHwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		MessageBox(resHwnd, "Normal -> Speicific Resolution", "Step Status",MB_OK);
		bStatus=EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &PrevDevMode);
		if (bStatus == 0)
		{
			MessageBox(resHwnd, "EnumDisplaySetting Failed", "Step Failed", MB_OK);
		}

		CurDevMode.dmPelsHeight = 600;
		CurDevMode.dmPelsWidth = 800;
		CurDevMode.dmBitsPerPel = 32;
		CurDevMode.dmFields = DM_BITSPERPEL|DM_PELSWIDTH | DM_PELSHEIGHT;
		lStatus=ChangeDisplaySettings(&CurDevMode, CDS_RESET | CDS_FULLSCREEN | CDS_UPDATEREGISTRY);

		bResolutionIsDefault = TRUE;
	}
	else
	{
		SetWindowLong(resHwnd, GWL_STYLE, dwStyle|WS_OVERLAPPEDWINDOW);
		MessageBox(resHwnd, "Specific -> Normal Resolution", "Step Status", MB_OK);
		CurDevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT| DM_BITSPERPEL;
		ChangeDisplaySettings(&PrevDevMode, CDS_RESET | CDS_FULLSCREEN | CDS_UPDATEREGISTRY);
		bResolutionIsDefault = FALSE;

	}

	return TRUE;
}