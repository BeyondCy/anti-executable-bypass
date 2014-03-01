/*
 *  Create a DLL library
 *
 * Written by Liviu Itoafa - Sept 2013
 * Licensed under Creative Commons Share Alike license.
 * Full details available here: http://creativecommons.org/licenses/by-sa/3.0
 *
 * Compile with cl:
 * cl /LD test_dll.c /link /out:NVCPL.dll
 *
 * Test:
 * rundll32 NVCPL.DLL,NvCplHandleHotplugEvents
 */
 
#pragma comment(lib, "User32.lib")  /* for MessageBox() */

#include <Windows.h>

  __declspec(dllexport) int NvCplHandleHotplugEvents(int p)  {
 		MessageBox(NULL, "Message", "Hello world!", MB_OK);	
        ExitProcess(0); 
}