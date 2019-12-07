.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib "..\Debug\BAAlib.lib"
ExitProcess PROTO:DWORD 
.stack 4096

 outnum PROTO : DWORD

 outstr PROTO : DWORD

 outsym PROTO : BYTE

 rand PROTO 

 pow PROTO : DWORD, : DWORD
.const
	L1 DWORD -32767
	L2 DWORD -99
	L3 DWORD 9
	L4 DWORD -9
	L5 DWORD Just, 0
	L6 BYTE 1, 0
	L7 DWORD string, 0
	L8 DWORD 1
	L9 DWORD 2
	L10 DWORD 3
	L11 DWORD 4
	L12 DWORD 52
	L13 DWORD  , 0
	L14 DWORD 8
.data
	minc DWORD 0
	minz DWORD 0
	minp DWORD 0
	minres DWORD 0
	mainx DWORD 0
	mainy DWORD 0
	mainc DWORD 0
	mainstrx WORD ?
	mainstrm BYTE ?
	mainstry WORD ?
	maint DWORD 0
	maint1 DWORD 0
	mainab DWORD 0

.code

min PROC minx :  DWORD miny :  DWORD miny1 :  DWORD miny2 :  DWORD 
mov eax, minres
ret
min ENDP
main PROC
