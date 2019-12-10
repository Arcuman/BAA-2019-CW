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
	L1 BYTE 'sdlklsd', 0
	L2 SDWORD 3
	L3 BYTE 'strhsd1 ', 0
	L4 SDWORD -1
	L5 SDWORD 1
	L6 SDWORD 0
	L7 SDWORD 10
	L8 BYTE 'number of digit = ', 0
	L9 BYTE 'number on position ', 0
	L10 BYTE ':', 0
	L11 SDWORD 32
	L12 BYTE 'Program completed successfully', 0
	L13 BYTE 'Program completed unsuccessfully', 0
.data
	_Inlengthstra1 DWORD ?
	_Inlengthstrhssd1 SDWORD 0
	_Inlengthstr1 DWORD ?
	_Inlengthstrhsd1 SDWORD 0
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
	push offset L1
	pop _Inlengthstra1

	push random
	push L2
	pop edx
	pop edx
	push L2
		call random
	push eax
	pop _Inlengthstrhssd1

	push offset L1
	pop _Inlengthstr1

	push random
	push L2
	pop edx
	pop edx
	push L2
		call random
	push eax
	pop _Inlengthstrhsd1

	mov edx, L2
	cmp edx, L2
	jz right1
	jmp next1
right1:
push offset L3
call outstr

push _Inlengthstrhsd1
call outnum

next1:	push L4
	pop _Inlengthlen

	push _Inlengthnum
	pop _InlengthtempNum

	push L5
	pop _Inlengthdegree

	mov edx, _InlengthtempNum
	cmp edx, L6
	jnz cycle1
	jmp continue1
 cycle1:	push _Inlengthnum
	push power
	push L7
	push _Inlengthdegree
	pop edx
	pop edx
	pop edx
	push _Inlengthdegree
	push L7
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
	push L5
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop _Inlengthdegree

	mov edx, _InlengthtempNum
	cmp edx, L6
	jnz cycle1
continue1:	push _Inlengthdegree
	push L5
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop _Inlengthlen

	mov eax, 0
	mov ebx,_Inlengthlen
	sub eax, ebx
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


push offset L8
call outstr

push _getDigitlen
call outnumline
	mov edx, _getDigitlen
	cmp edx, _getDigitposit
	jg right2
	jl wrong2
	jmp next2
right2:	push _getDigita
	push power
	push L7
	push _getDigitposit
	pop edx
	pop edx
	pop edx
	push _getDigitposit
	push L7
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
	push L7
	pop ebx
	pop eax
	cmp ebx,0
	je SOMETHINGWRONG
	cdq
	idiv ebx
	push edx
	pop _getDigitanswer


push offset L9
call outstr

push _getDigitposit
call outnum

push offset L10
call outstrline

push _getDigitanswer
call outnumline
	mov eax, L6
	ret

SOMETHINGWRONG:
push offset null_division
call outstrline
call system_pause
push -1
call ExitProcess
	jmp next2

wrong2:	mov eax, L4
	ret

next2:	mov eax, L4
	ret
_getDigitb ENDP
main PROC
	push L11
	pop maina

	push _getDigitb
	push maina
	push L6
	pop edx
	pop edx
	pop edx
	push L6
	push maina
		call _getDigitb
	push eax
	pop mainfunc

	mov edx, mainfunc
	cmp edx, L6
	jz right3
	jnz wrong3
	jmp next3
right3:
push offset L12
call outstrline
	jmp next3

wrong3:
push offset L13
call outstrline

next3:call system_pause
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