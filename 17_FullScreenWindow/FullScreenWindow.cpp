#include<Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL sw_ToggleFullScreen(HWND,BOOL);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int nCmdShow)
{
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("My Full Screen Class");
	
	wndclass.cbClsExtra = NULL;
	wndclass.cbSize = sizeof(WNDCLASSEX);
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

	hwnd = CreateWindow(szAppName, TEXT("Full Screen Trial"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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
	BOOL ScreenStatus=FALSE; // Default this should be false as initially window is at normal position
	BOOL CursorStatus=FALSE; // this is TRUE if you dont want cursor at FullScreen and FALSE if you want cursor even after FullScreen

	switch (iMsg)
	{
	case WM_CREATE:
		MessageBox(hwnd, "Inside WM_CREATE", "Step Success", MB_OK);
		//ghwnd = (HWND)GetWindowLong(hwnd, GWLP_WNDPROC);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'F':
		case 'f':
			MessageBox(hwnd, "Under WM_KEYDOWN:F", "Step Success", MB_OK);
			ScreenStatus=sw_ToggleFullScreen(hwnd,CursorStatus);
			break;

		case VK_ESCAPE:
			MessageBox(hwnd,"Inside VK_ESCAPE now closing window","Step Success",MB_OK);
			DestroyWindow(hwnd);
			break;
		}
		break;
	
	case WM_DESTROY:
		MessageBox(hwnd, "Under WM_DESTROY", "Step Success", MB_OK);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

BOOL sw_ToggleFullScreen(HWND Togglehwnd,BOOL CursorState)
{
	static BOOL bScreenStatus=FALSE;

	MessageBox(NULL, "Inside sw_ToggleFullScreen", "Step Success", MB_OK);
	
	static WINDOWPLACEMENT WndPlacement; //For currnet window placement get and set (Structure)
	MONITORINFO UserMonitorInfo;
	UserMonitorInfo.cbSize = sizeof(MONITORINFO);
	HMONITOR hMonitor;
	BOOL bStatus;
	static LONG CurrentWindowStyle;
	LONG lStatus;

	if ( bScreenStatus== FALSE)
	{
		MessageBox(Togglehwnd,"Toggle from: Normal Screen->Full Screen","Step Success",MB_OK);
		{
			//Getting Window style
			CurrentWindowStyle=GetWindowLong(Togglehwnd, GWL_STYLE);

			//Geting Window Current Placement
			bStatus=GetWindowPlacement(Togglehwnd, &WndPlacement);
			if (bStatus == 0)
			{
				MessageBox(Togglehwnd, "Failed to get current window placement...Closing Application", "Step Failed", MB_OK);
				DestroyWindow(Togglehwnd);
			}
			else
			{
				MessageBox(Togglehwnd, "Successfully stored current window placement", "Step Success", MB_OK);
			}

			//Getting Monitor Handle for GetMonitorInfo
			hMonitor = MonitorFromWindow(Togglehwnd, MONITOR_DEFAULTTOPRIMARY);

			//Getting user Primary monitor status
			bStatus = GetMonitorInfo(hMonitor, &UserMonitorInfo);
			if (bStatus == 0)
			{
				MessageBox(Togglehwnd, "Failed to get monitor info..clsoing application", "Step Failed",MB_OK);
				DestroyWindow(Togglehwnd);
			}
			else
			{
				MessageBox(Togglehwnd, "Succesfully got monitor info", "Step Success", MB_OK);
			}

			//Removing Current Window Style
			lStatus = SetWindowLong(Togglehwnd, GWL_STYLE, CurrentWindowStyle &~WS_OVERLAPPEDWINDOW);
			if(lStatus == 0)
			{
				MessageBox(Togglehwnd, "Failed to Execture SetWindowLong", "Step Failed", MB_OK);
			}
			else
			{
				MessageBox(Togglehwnd, "Successfully Set Window Style", "Step Success", MB_OK);
			}

			//Setting window Full Screen
			bStatus=SetWindowPos(Togglehwnd, 
					HWND_TOP, 
					UserMonitorInfo.rcMonitor.left, 
					UserMonitorInfo.rcMonitor.top, 
					UserMonitorInfo.rcMonitor.right - UserMonitorInfo.rcMonitor.left, 
					UserMonitorInfo.rcMonitor.bottom - UserMonitorInfo.rcMonitor.top,
					SWP_NOZORDER | SWP_FRAMECHANGED);
			if (bStatus == 0)
			{
				MessageBox(Togglehwnd, "Failed to Full Screen at SetWindowPos", "Step Failed", MB_OK);
			}
			else
			{
				MessageBox(Togglehwnd, "Full Screening your Window", "Step Success", MB_OK);
			}
		}
		if (CursorState == TRUE)
		{
			ShowCursor(FALSE);
		}
		else
		{
			ShowCursor(TRUE);
		}
		bScreenStatus = TRUE;
		return bScreenStatus;
	}
	else
	{
		MessageBox(Togglehwnd, "Toggle from: Full Screen->Normal Screen", "Step Success", MB_OK);
		{
			//Setting Window long back to WS_OVERLAPPEDWINDOW
			lStatus = SetWindowLong(Togglehwnd, GWL_STYLE, CurrentWindowStyle | WS_OVERLAPPEDWINDOW);
			if (lStatus == 0)
			{
				MessageBox(Togglehwnd, "Failed to SetWindowLong", "Step Failed", MB_OK);
			}
			else
			{
				MessageBox(Togglehwnd, "Set WS_OVERLAPPEDWINDOW", "Step Success", MB_OK);
			}
			
			//Setting Window Placement as previous (Using structure value we got by calling GetWindowPlacement)
			bStatus=SetWindowPlacement(Togglehwnd, &WndPlacement);
			if (bStatus)
			{
				MessageBox(Togglehwnd, "Failed to set window previous placement", "Step Failed", MB_OK);
			}
			else
			{
				MessageBox(Togglehwnd, "Successfully set window previous placement", "Step success", MB_OK);
			}
			
			//Setting window position (automatically set by using structure used in SetWindowPlacement)
			bStatus=SetWindowPos(Togglehwnd,
				HWND_TOP,
				0,
				0,
				0,
				0,
				SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER
				);
			if (bStatus == 0)
			{
				MessageBox(Togglehwnd, "Failed to Normalized Screen at SetWindowPos", "Step Failed", MB_OK);
			}
			else
			{
				MessageBox(Togglehwnd, "Window is at normal position", "Step Success", MB_OK);
			}

		}
		bScreenStatus = FALSE;
		ShowCursor(TRUE);
		return bScreenStatus;
	}
}