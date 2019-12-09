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
	L1 BYTE '123', 0
	L2 BYTE ' ', 0
	L3 SDWORD 0
	L4 SDWORD 9
	L5 BYTE 'x = ', 0
	L6 SDWORD 3
	L7 SDWORD -9
	L8 BYTE 'c = ', 0
	L9 BYTE 'Just', 0
	L10 BYTE 'strx = ', 0
	L11 BYTE '1', 0
	L12 BYTE 'F', 0
	L13 BYTE 'strm = ', 0
	L14 BYTE 'stry = ', 0
	L15 BYTE 'TRUE BLOCK', 0
	L16 BYTE 'FALSE BLOCK', 0
	L17 SDWORD 2
	L18 BYTE 't1 = ', 0
	L19 BYTE 'cycle start:', 0
	L20 SDWORD 1
	L21 BYTE 'cycle end:', 0
.data
	pow1x DWORD ?
	pow1y DWORD ?
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
	push offset L1
	pop pow1x

	push offset L1
	pop pow1y

	mov esi, pow1x
	mov edi, pow1y

	 push pow1x
	 call lenght
	 mov ebx,eax
	 push pow1y
	 call lenght
	 cmp ebx,eax
	 jne continue1
	 mov ecx,eax
	 repe cmpsb
	jnz cycle1
	jmp continue1
 cycle1:
push pow1x
call outstr

push offset L2
call outstr
	jnz cycle1
continue1:
push pow1y
call outstrline

push pow1c
call outnumline
	mov eax, L3
	ret
pow1 ENDP
main PROC
	push L4
	pop mainx


push offset L5
call outstr

push mainx
call outnumline
	push pow1
	push L6
	pop edx
	pop edx
	push L6
		call pow1
	push eax
	pop mainx

	push L7
	push L4
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop mainc


push offset L8
call outstr

push mainc
call outnumline
	push offset L9
	pop mainstrx


push offset L10
call outstr

push mainstrx
call outstrline
	push offset L11
	pop mainstrm

	push offset L12
	pop mainstrf


push offset L13
call outstr

push mainstrm
call outstrline
	push offset L9
	pop mainstry


push offset L14
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
	 jne wrong1
	 mov ecx,eax
	 repe cmpsb
	jnz right1
	jz wrong1
	jmp next1
right1:
push offset L15
call outstrline
	jmp next1

wrong1:
push offset L16
call outstr

next1:	mov esi, mainstrm
	mov edi, mainstrf

	 push mainstrm
	 call lenght
	 mov ebx,eax
	 push mainstrf
	 call lenght
	 cmp ebx,eax
	 jne wrong2
	 mov ecx,eax
	 repe cmpsb
	jnz right2
	jz wrong2
	jmp next2
right2:
push offset L15
call outstrline
	jmp next2

wrong2:
push offset L16
call outstr

next2:	push L17
	pop maint1


push offset L18
call outstr

push maint1
call outnumline
	push L3
	pop mainab


push offset L19
call outstrline
	mov esi, mainstrx
	mov edi, mainstry

	 push mainstrx
	 call lenght
	 mov ebx,eax
	 push mainstry
	 call lenght
	 cmp ebx,eax
	 jne continue2
	 mov ecx,eax
	 repe cmpsb
	jz cycle2
	jmp continue2
 cycle2:
push mainab
call outnum

push offset L2
call outstr
	push mainab
	push L20
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop mainab

	jz cycle2
continue2:
push offset L21
call outstrline

push offset L2
call outstrline

push mainab
call outnumline
call system_pause
push 0
call ExitProcess
main ENDP
end main