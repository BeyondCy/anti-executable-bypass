/*
 * Create Thread Local Storage callbacks using cl compiler
 * Register multiple TLS callbacks
 *
 * Written by Liviu Itoafa - Sept 2013
 * Licensed under Creative Commons Share Alike license.
 * Full details available here: http://creativecommons.org/licenses/by-sa/3.0
 *
 * Based on documentation from 
 * Thread Local Storage, part 3: Compiler and linker support for implicit TLS
 * http://www.nynaeve.net/?p=183
 * 
 * Compile:
 * > cl /EHsc test_tls.c
 *
 * Tested with on:
 * Microsoft (R) C/C++ Optimizing Compiler Version 17.00.50727.1 for x86 (VS2012)
 * Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 15.00.21022.08 for 80x86 (VS2008)
 */

#pragma comment(lib, "User32.lib")  /* for MessageBox() */

#include <Windows.h>

/* Pointer to a TLS callback function */
typedef void (__stdcall *TLS_CALLBACK_PTR)(void *instance, int reason, void *reserved);

/* Semi-documented in tlssup.c 
 * Defined in C:\Program Files\Windows Kits\8.0\include\um\winnt.h, as IMAGE_TLS_DIRECTORY
 */
typedef struct TLS_DATA {
	int tls_start;						// start of TLS data
	int tls_end;						// end of TLS data
	int* tls_index;						// address of tls_index
	TLS_CALLBACK_PTR * tls_functions;	// array of addresses of TLS callbacks
	int fill_size;						// size of TLS zero fill (0)
	int characteristics;				// TLS characteristics (0)
} TLS_DATA;

/* Thread Local Storage index for this .EXE */
long _tls_index = 0;

void __stdcall callback(void *instance, int reason, void *reserved) {
	if(reason == DLL_PROCESS_ATTACH) {  
		MessageBox(NULL, "Hidden message", "Callback", MB_OK);	
        //ExitProcess(0);        
	}
}

void __stdcall callback2(void *instance, int reason, void *reserved) {
	if(reason == DLL_PROCESS_ATTACH) {  
		MessageBox(NULL, "Hidden message 2", "Callback 2", MB_OK);	
        ExitProcess(0);        
	}
}

/* Thread callbacks */
TLS_CALLBACK_PTR tls_functions[3] = {&callback, &callback2, NULL};

/* Variable name MUST be _tls_used, as the linker looks for a variable by that name */
extern TLS_DATA _tls_used={0, 0, &_tls_index, tls_functions, 0, 0};

int main(int argc, char* argv[]) {
	/* Will never be called, as the last TLS callback does ExitProcess() */
	MessageBox(NULL, "Hello, world!", "From main!", MB_OK);

	return 0;
}
