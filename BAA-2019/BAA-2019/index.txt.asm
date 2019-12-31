.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib "..\Debug\BAAlib.lib"
ExitProcess PROTO:DWORD 
.stack 4096

 outnum PROTO : DWORD

 outstr PROTO : DWORD

 outstrline PROTO : DWORD

 outnumline PROTO : DWORD

 system_pause PROTO 

 random PROTO  : DWORD

 lenght PROTO  : DWORD

 power PROTO : DWORD, : DWORD
.const
 null_division BYTE 'ERROR: DIVISION BY ZERO', 0
 overflow BYTE 'ERROR: VARIABLE OVERFLOW', 0 
	L1 SDWORD 1
	L2 SDWORD 10
	L3 BYTE 'Jora JOra', 0
.data
	maini SDWORD 0

.code

main PROC
	push L1
	pop maini

	mov edx, maini
	cmp edx, L2
	jl cycle1
	jmp continue1
 cycle1:
push offset L3
call outstrline
	mov eax,maini
	mov ebx,L1
	add eax, ebx
	jo EXIT_OVERFLOW
	mov maini , eax
	mov edx, maini
	cmp edx, L2
	jl cycle1
continue1:call system_pause
push 0
call ExitProcess
SOMETHINGWRONG:
push offset null_division
call outstrline
call system_pause
push -1
call ExitProcess
EXIT_OVERFLOW:
push offset overflow
call outstrline
call system_pause
push -2
call ExitProcess
main ENDP
end main