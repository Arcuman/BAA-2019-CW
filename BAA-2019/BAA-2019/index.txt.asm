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
	L1 SDWORD 2
	L2 SDWORD 3
	L3 SDWORD 10
	L4 SDWORD 0
	L5 BYTE 'i = ', 0
	L6 SDWORD 5
	L7 BYTE 'a = ', 0
	L8 SDWORD 1
.data
	maina SDWORD 0
	maini SDWORD 0

.code

_abs PROC _absa :  SDWORD 
	mov eax,_absa
	mov ebx,L1
	add eax, ebx
	jo EXIT_OVERFLOW
	mov _absa , eax
	mov edx, _absa
	cmp edx, L2
	jg right1
	jmp next1
right1:	push L3
	pop _absa

	mov eax, _absa
	ret

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

next1:	mov eax, L4
	ret
_abs ENDP
_out PROC _outi :  SDWORD 

push offset L5
call outstr

push _outi
call outnumline
	ret

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
_out ENDP
main PROC
	push random
	push L6
	pop edx
	pop edx
	push L6
		call random
	push eax
	pop maina


push offset L7
call outstr

push maina
call outnumline
	push maina
	mov eax, 0
	pop ebx
	sub eax, ebx
	push eax
	push L8
	push _abs
	push L8
	pop edx
	pop edx
	push L8
		call _abs
	push eax
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	push L2
	pop eax
	pop ebx
	imul ebx
	jo EXIT_OVERFLOW
	push eax
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop maini

	mov edx, maini
	cmp edx, L4
	jg cycle1
	jmp continue1
 cycle1:
push maini

call _out
	mov eax,maini
	mov ebx,L8
	sub eax, ebx
	jo EXIT_OVERFLOW
	mov maini , eax
	mov edx, maini
	cmp edx, L4
	jg cycle1
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