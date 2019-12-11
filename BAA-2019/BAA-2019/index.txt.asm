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
	L1 SDWORD 1
	L2 SDWORD 5
	L3 SDWORD 2
	L4 BYTE 'qwerty', 0
.data
	mainforfunc SDWORD 0
	mainy DWORD ?

.code

_power PROC _powera :  SDWORD 
	push _powera
	push L1
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop _powera

	mov edx, _powera
	cmp edx, L2
	jz right1
	jnz wrong1
	jmp next1
right1:	mov eax, _powera
	ret

SOMETHINGWRONG:
push offset null_division
call outstrline
call system_pause
push -1
call ExitProcess
	jmp next1

wrong1:	push _power
	push _powera
	pop edx
	pop edx
	push _powera
		call _power
	push eax
	pop _powera


next1:	mov eax, _powera
	ret
_power ENDP
main PROC
	push _power
	push L3
	pop edx
	pop edx
	push L3
		call _power
	push eax
	pop mainforfunc


push mainforfunc
call outnumline
	push offset L4
	pop mainy

call system_pause
push 0
call ExitProcess
SOMETHINGWRONG:
push offset null_division
call outstrline
call system_pause
push -1
call ExitProcess
main ENDP
end main