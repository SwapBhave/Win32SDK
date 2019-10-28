#include<Windows.h>
#include"Server.h"

BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

/*extern "C" double MakeAOC(double num1)
{
 	double PI = 3.14;
	double iAOC;
	// code
	iAOC = PI * (num1*num1);
	return(iAOC);
}*/

extern "C" double Area(double sqr)
{
	double PI = 3.14f;
	double output = PI * (sqr*sqr);

	return (output);
}

