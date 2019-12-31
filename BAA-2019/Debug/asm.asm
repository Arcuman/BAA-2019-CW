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
	L2 SDWORD 0
	L3 SDWORD 10
	L4 BYTE 'Hello world', 0
	L5 BYTE 'Length of string: ', 0
	L6 BYTE ' = ', 0
	L7 BYTE 'factorial: ', 0
	L8 BYTE 'Number of digit in facrotial: ', 0
	L9 BYTE 'position generated before cheking: ', 0
	L10 BYTE 'position generated after cheking: ', 0
	L11 BYTE 'The digit on position: ', 0
	L12 BYTE ' is:', 0
.data
	_factnewN SDWORD 0
	_Inlengthlen SDWORD 0
	_InlengthtempNum SDWORD 0
	_Inlengthdegree SDWORD 0
	_getDigitanswer SDWORD 0
	_getDigittempNum SDWORD 0
	mainstr DWORD ?
	mainlen SDWORD 0
	mainfactvar SDWORD 0
	mainLenFact SDWORD 0
	mainposition SDWORD 0
	maintempPos SDWORD 0
	maindigit SDWORD 0

.code

_fact PROC _factN :  SDWORD 
	push _factN
	push L1
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop _factnewN

	mov edx, _factN
	cmp edx, L2
	jz right1
	jnz wrong1
	jmp next1
right1:	mov eax, L1
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
	jmp next1

wrong1:	push _factN
	push _fact
	push _factnewN
	pop edx
	pop edx
	push _factnewN
		call _fact
	push eax
	pop eax
	pop ebx
	imul ebx
	jo EXIT_OVERFLOW
	push eax
	pop _factN

	mov eax, _factN
	ret

next1:	mov eax, L1
	ret
_fact ENDP
_Inlength PROC _Inlengthnum :  SDWORD 
	push L2
	pop _Inlengthlen

	push _Inlengthnum
	pop _InlengthtempNum

	push L1
	pop _Inlengthdegree

	mov edx, _InlengthtempNum
	cmp edx, L2
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

	mov eax,_Inlengthdegree
	mov ebx,L1
	add eax, ebx
	jo EXIT_OVERFLOW
	mov _Inlengthdegree , eax
	mov edx, _InlengthtempNum
	cmp edx, L2
	jnz cycle1
continue1:	push _Inlengthdegree
	push L1
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

EXIT_OVERFLOW:
push offset overflow
call outstrline
call system_pause
push -2
call ExitProcess
_Inlength ENDP
_getDigit PROC _getDigitnum :  SDWORD , _getDigitposit :  SDWORD 
	push _getDigitnum
	pop _getDigittempNum

	push _getDigitnum
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

	mov eax, _getDigitanswer
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
_getDigit ENDP
main PROC
	push offset L4
	pop mainstr

	push lenght
	push mainstr
	pop edx
	pop edx
	push mainstr
		call lenght
	push eax
	pop mainlen


push offset L5
call outstr

push mainstr
call outstr

push offset L6
call outstr

push mainlen
call outnumline
	push _fact
	push mainlen
	pop edx
	pop edx
	push mainlen
		call _fact
	push eax
	pop mainfactvar


push offset L7
call outstr

push mainfactvar
call outnumline
	push _Inlength
	push mainfactvar
	pop edx
	pop edx
	push mainfactvar
		call _Inlength
	push eax
	pop mainLenFact


push offset L8
call outstr

push mainLenFact
call outnumline
	push random
	push mainLenFact
	pop edx
	pop edx
	push mainLenFact
		call random
	push eax
	pop mainposition

	mov edx, mainposition
	cmp edx, L2
	jz cycle2
	jmp continue2
 cycle2:	push random
	push mainLenFact
	pop edx
	pop edx
	push mainLenFact
		call random
	push eax
	pop mainposition

	mov edx, mainposition
	cmp edx, L2
	jz cycle2
continue2:
push offset L9
call outstr

push mainposition
call outnumline
	mov edx, mainposition
	cmp edx, L2
	jle wrong2
	jmp next2
wrong2:	push mainposition
	mov eax, 0
	pop ebx
	sub eax, ebx
	push eax
	pop mainposition


next2:
push offset L10
call outstr

push mainposition
call outnumline
	push mainLenFact
	push mainposition
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop maintempPos

	push _getDigit
	push mainfactvar
	push maintempPos
	pop edx
	pop edx
	pop edx
	push maintempPos
	push mainfactvar
		call _getDigit
	push eax
	pop maindigit


push offset L11
call outstr

push mainposition
call outnum

push offset L12
call outstrline

push maindigit
call outnumline
call system_pause
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