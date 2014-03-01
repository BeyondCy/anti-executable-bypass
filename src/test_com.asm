; Hello World!
; Assembly language - x86 DOS
;
; Written by Liviu Itoafa - Sept 2013
; Licensed under Creative Commons Share Alike license.
; Full details available here: http://creativecommons.org/licenses/by-sa/3.0
;
; Compile into OMF format
; > ml /omf test_com.asm
;
; Link with 16bit linker
; Microsoft (R) Segmented Executable Linker  Version 5.60.339 Dec  5 1994
; Copyright (C) Microsoft Corp 1984-1993.  All rights reserved.
; > link16.exe  test_com.obj,,nul,,,
;
; Convert to COM
; > exe2bin test_com.exe test_com.com
;
; References:
; DOS INT 21h - DOS Function Codes
; http://spike.scu.edu.au/~barry/interrupts.html

code segment
assume cs:code, ds:code
org 100h        ; .com files always load at 100h

start:
    mov dx, offset msg
    mov ah, 9       ; print string whose address is in dx register
    int 21h

    mov ah, 4Ch     ; end program
    int 21h

msg db 'Hello World!',0Dh,0Ah,'$'                  

code ends
end start