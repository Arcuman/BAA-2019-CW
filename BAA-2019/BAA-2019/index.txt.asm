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
	L1 SDWORD 3
	L2 SDWORD 5
	L3 SDWORD 10
	L4 SDWORD 0
	L5 SDWORD 100
	L6 SDWORD 1
	L7 SDWORD 1000
	L8 BYTE 'c rand = ', 0
	L9 SDWORD 9
	L10 BYTE 'x = ', 0
	L11 SDWORD -9
	L12 BYTE 'c = ', 0
	L13 BYTE 'Just', 0
	L14 BYTE 'strx = ', 0
	L15 BYTE '1', 0
	L16 BYTE 'F', 0
	L17 BYTE 'strm = ', 0
	L18 BYTE 'stry = ', 0
	L19 BYTE 'TRUE BLOCK', 0
	L20 BYTE 'FALSE BLOCK', 0
	L21 SDWORD 2
	L22 BYTE 't1 = ', 0
	L23 BYTE 'cycle start:', 0
	L24 BYTE ' ', 0
	L25 BYTE 'cycle end:', 0
.data
	pow1x SDWORD 0
	pow1y SDWORD 0
	pow1count SDWORD 0
	mainx SDWORD 0
	mainc SDWORD 0
	mainstrx DWORD ?
	mainstrm DWORD ?
	mainstrf DWORD ?
	mainstry DWORD ?
	maint1 SDWORD 0
	mainab SDWORD 0

.code

pow1 PROC pow1c :  SDWORD 
	push L1
	pop pow1x

	push pow1x
	mov eax, 0
	pop ebx
	sub eax, ebx
	push eax
	push L2
	push pow1x
	mov eax, 0
	pop ebx
	sub eax, ebx
	push eax
	push L1
	pop eax
	pop ebx
	mul ebx
	push eax
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push pow1x
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push L3
	pop eax
	pop ebx
	mul ebx
	push eax
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop pow1y


push pow1y
call outnumline

push pow1c
call outnumline
	mov edx, pow1c
	cmp edx, L4
	jl right1
	jg wrong1
	jmp next1
wrong1:	push L5
	push pow1x
	mov eax, 0
	pop ebx
	sub eax, ebx
	push eax
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop pow1count

	mov eax, pow1count
	ret
	jmp next1

right1:	push L6
	pop pow1count


next1:	mov edx, pow1count
	cmp edx, L5
	jl cycle1
	jmp continue1
 cycle1:	push L7
	pop pow1c


push offset L8
call outstr

push pow1c
call outnumline
	push pow1count
	push L6
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop pow1count

	mov edx, pow1count
	cmp edx, L5
	jl cycle1
continue1:	mov eax, L4
	ret
pow1 ENDP
main PROC
	push L9
	pop mainx


push offset L10
call outstr

push mainx
call outnumline
	push pow1
	push L1
	pop edx
	pop edx
	push L1
		call pow1
	push eax
	pop mainx

	push L11
	push L9
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop mainc


push offset L12
call outstr

push mainc
call outnumline
	push offset L13
	pop mainstrx


push offset L14
call outstr

push mainstrx
call outstrline
	push offset L15
	pop mainstrm

	push offset L16
	pop mainstrf


push offset L17
call outstr

push mainstrm
call outstrline
	push offset L13
	pop mainstry


push offset L18
call outstr

push mainstry
call outstrline

push mainstrx
call outstrline
	mov esi, mainstrx
	mov edi, mainstry

	 push mainstrx
	 call lenght
	 mov ebx,eax
	 push mainstry
	 call lenght
	 cmp ebx,eax
	 jne wrong2
	 mov ecx,eax
	 repe cmpsb
	jnz right2
	jz wrong2
	jmp next2
right2:
push offset L19
call outstrline
	jmp next2

wrong2:
push offset L20
call outstr

next2:	mov esi, mainstrm
	mov edi, mainstrf

	 push mainstrm
	 call lenght
	 mov ebx,eax
	 push mainstrf
	 call lenght
	 cmp ebx,eax
	 jne wrong3
	 mov ecx,eax
	 repe cmpsb
	jnz right3
	jz wrong3
	jmp next3
right3:
push offset L19
call outstrline
	jmp next3

wrong3:
push offset L20
call outstr

next3:	push L21
	pop maint1


push offset L22
call outstr

push maint1
call outnumline
	push L4
	pop mainab


push offset L23
call outstrline
	jnz cycle2
	jmp continue2
 cycle2:
push mainab
call outnum

push offset L24
call outstr
	push mainab
	push L6
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop mainab

	jnz cycle2
continue2:
push offset L25
call outstrline

push offset L24
call outstrline

push mainab
call outnumline
call system_pause
push 0
call ExitProcess
main ENDP
end main