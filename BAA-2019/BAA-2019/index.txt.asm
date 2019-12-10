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
	L1 SDWORD 0
	L2 SDWORD 1
	L3 SDWORD 10
	L4 BYTE 'number of digit = ', 0
	L5 BYTE 'number on position ', 0
	L6 BYTE ':', 0
	L7 SDWORD -1
	L8 SDWORD 32
	L9 BYTE 'Program completed successfully', 0
	L10 BYTE 'Program completed unsuccessfully', 0
.data
	_Inlengthlen SDWORD 0
	_InlengthtempNum SDWORD 0
	_Inlengthdegree SDWORD 0
	_getDigitlen SDWORD 0
	_getDigitanswer SDWORD 0
	_getDigittempNum SDWORD 0
	maina SDWORD 0
	mainfunc SDWORD 0

.code

_Inlength PROC _Inlengthnum :  SDWORD 
	push L1
	pop _Inlengthlen

	push _Inlengthnum
	pop _InlengthtempNum

	push L2
	pop _Inlengthdegree

	mov edx, _InlengthtempNum
	cmp edx, L1
	jnz cycle1
	jmp continue1
 cycle1:	push _Inlengthnum
	push power
	push L3
	push _Inlengthdegree
	pop edx
	pop edx
	pop edx
	push _Inlengthdegree
	push L3
		call power
	push eax
	pop ebx
	pop eax
	cmp ebx,0
	je SOMETHINGWRONG
	cdq
	idiv ebx
	push eax
	pop _InlengthtempNum

	push _Inlengthdegree
	push L2
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop _Inlengthdegree

	mov edx, _InlengthtempNum
	cmp edx, L1
	jnz cycle1
continue1:	push _Inlengthdegree
	push L2
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop _Inlengthlen

	mov eax, _Inlengthlen
	ret

SOMETHINGWRONG:
push offset null_division
call outstrline
call system_pause
push -1
call ExitProcess
_Inlength ENDP
_getDigitb PROC _getDigita :  SDWORD , _getDigitposit :  SDWORD 
	push _Inlength
	push _getDigita
	pop edx
	pop edx
	push _getDigita
		call _Inlength
	push eax
	pop _getDigitlen

	push _getDigita
	pop _getDigittempNum


push offset L4
call outstr

push _getDigitlen
call outnumline
	mov edx, _getDigitlen
	cmp edx, _getDigitposit
	jg right1
	jl wrong1
	jmp next1
right1:	push _getDigita
	push power
	push L3
	push _getDigitposit
	pop edx
	pop edx
	pop edx
	push _getDigitposit
	push L3
		call power
	push eax
	pop ebx
	pop eax
	cmp ebx,0
	je SOMETHINGWRONG
	cdq
	idiv ebx
	push eax
	pop _getDigittempNum

	push _getDigittempNum
	push L3
	pop ebx
	pop eax
	cmp ebx,0
	je SOMETHINGWRONG
	cdq
	idiv ebx
	push edx
	pop _getDigitanswer


push offset L5
call outstr

push _getDigitposit
call outnum

push offset L6
call outstrline

push _getDigitanswer
call outnumline
	mov eax, L1
	ret

SOMETHINGWRONG:
push offset null_division
call outstrline
call system_pause
push -1
call ExitProcess
	jmp next1

wrong1:	mov eax, L7
	ret

next1:	mov eax, L7
	ret
_getDigitb ENDP
main PROC
	push L8
	pop maina

	push _getDigitb
	push maina
	push L1
	pop edx
	pop edx
	pop edx
	push L1
	push maina
		call _getDigitb
	push eax
	pop mainfunc

	mov edx, mainfunc
	cmp edx, L1
	jz right2
	jnz wrong2
	jmp next2
right2:
push offset L9
call outstrline
	jmp next2

wrong2:
push offset L10
call outstrline

next2:call system_pause
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