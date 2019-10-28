#include<Windows.h>
#include"DialogBox.h"

/*typedef struct INPUT
{
	char name[50], address[50];
	int age, mstatus;
	float sal;
}in;
*/

//declare callback function
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
//Globally declare structure

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
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	//class register
	RegisterClassEx(&wndclass);
	//create window
	hwnd = CreateWindow(szAppName, TEXT("MyApp"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
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
	HINSTANCE hInst;
	switch (iMsg)
	{
	case WM_CREATE:
		hInst = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
		DialogBox(hInst,"DATAENTRY", hwnd, (DLGPROC)MyDlgProc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	//DefWindowProc
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

BOOL CALLBACK MyDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	char salrs[6], salps[3];
	switch (iMsg)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hDlg, ID_ETNAME));
		SendDlgItemMessage(hDlg, ID_RBMARRIED,BM_SETCHECK, 1, 0);
		return(TRUE);
		
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_PBCONTINUE:
			EndDialog(hDlg, 0);
			DestroyWindow(0);
			break;

		case IDOK:
			//GetDlgItemText(hDlg, ID_ETNAME,in.name, 50);
			//GetDlgItemText(hDlg, ID_ETADDRESS, in.address, 50);
			//GetDlgItemInt(hDlg, ID_ETAGE,in.age,TRUE);
			//GetDlgItemText(hDlg, ID_ETADDRESS, in.address, 50);
			//GetDlgItemText(hDlg, ID_ETSALRS,salrs,6);
			//GetDlgItemText(hDlg, ID_ETSALPS,salps, 3);
			//in.sal = atoi(salrs) + (float)atoi(salps / 100);
			//in.mstatus = SendDlgItemMessage(hDlg, ID_RBMARRIED, BM_GETCHECK, 0, 0);
			//EndDialog(hDlg, 0);
			break;

		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;
		}
		return(TRUE);
	}
	return(FALSE);
}

