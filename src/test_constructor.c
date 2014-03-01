/*
 *   Initializer/finalizer sample for MSVC and GCC.
 *
 * Written by Liviu Itoafa - Sept 2013
 * Licensed under Creative Commons Share Alike license.
 * Full details available here: http://creativecommons.org/licenses/by-sa/3.0
 *
 * Cross-compile with gcc:
 * /usr/bin/i586-mingw32msvc-gcc -Wall -Wall test_cons.c 
 *
 * Compile with cl:
 * cl /EHsc test_cons.c
 */

#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER                         /* compiled with cl */
    #define CCALL __cdecl

    #pragma section(".CRT$XCU",read)

    #define INITIALIZER(f) \
       static void __cdecl f(void); \
       __declspec(allocate(".CRT$XCU")) void (__cdecl*f##_)(void) = f; \
       static void __cdecl f(void)
#elif defined(__GNUC__)                 /* compiled with gcc */
    #define CCALL
    #define INITIALIZER(f) \
       static void f(void) __attribute__((constructor)); \
       static void f(void)
#endif

static void CCALL finalize(void)
{
   printf("finalize\n");
}

INITIALIZER(initialize)
{
   printf("initialize\n");
   atexit(finalize);
}

int CCALL main(int argc,const char*const* argv)
{
    printf("Hello world from MAIN!\n");

    return 42;
}
