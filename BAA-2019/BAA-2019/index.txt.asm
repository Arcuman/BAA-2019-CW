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

 power PROTO : DWORD, : DWORD
.const
	L1 SDWORD 0
	L2 SDWORD 101
	L3 SDWORD 1
	L4 SDWORD 100
	L5 SDWORD 1000
	L6 BYTE 'c rand = ', 0
	L7 SDWORD 9
	L8 BYTE 'x = ', 0
	L9 SDWORD 3
	L10 SDWORD -9
	L11 BYTE 'y = ', 0
	L12 BYTE 'c = ', 0
	L13 BYTE 'Just', 0
	L14 BYTE 'strx = ', 0
	L15 BYTE '1', 0
	L16 BYTE 'strm = ', 0
	L17 BYTE 'string', 0
	L18 BYTE 'stry = ', 0
	L19 SDWORD 2
	L20 BYTE 't1 = ', 0
	L21 BYTE 'cycle start:', 0
	L22 SDWORD 5
	L23 BYTE ' ', 0
	L24 BYTE 'cycle end:', 0
.data
	pow1count SDWORD 0
	mainx SDWORD 0
	mainy SDWORD 0
	mainc SDWORD 0
	mainstrx DWORD ?
	mainstrm DWORD ?
	mainstry DWORD ?
	maint1 SDWORD 0
	mainab SDWORD 0

.code

pow1 PROC pow1c :  SDWORD 

push pow1c
call outnumline
	mov edx, pow1c
	cmp edx, L1
	jg right1
	jl wrong1
	jmp next1
wrong1:	push L2
	pop pow1count

	jmp next1

right1:	push L3
	pop pow1count


next1:	mov edx, pow1count
	cmp edx, L4
	jl cycle1
	jmp continue1
 cycle1:	push random
	push L5
	pop edx
	pop edx
	push L5
		call random
	push eax
	pop pow1c


push offset L6
call outstr

push pow1c
call outnumline
	push pow1count
	push L3
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop pow1count

	mov edx, pow1count
	cmp edx, L4
	jl cycle1
continue1:	mov eax, L1
	ret
pow1 ENDP
main PROC
	push L7
	pop mainx


push offset L8
call outstr

push mainx
call outnumline
	push pow1
	push L9
	pop edx
	pop edx
	push L9
		call pow1
	push eax
	pop mainx

	push L10
	pop mainy


push offset L11
call outstr

push mainy
call outnumline
	push L10
	push L7
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
call outstr

push mainstrm
call outstrline
	push offset L17
	pop mainstry


push offset L18
call outstr

push mainstry
call outstrline
	push L19
	pop maint1


push offset L20
call outstr

push maint1
call outnumline
	push L1
	pop mainab


push offset L21
call outstrline
	mov edx, mainab
	cmp edx, L22
	jnz cycle2
	jmp continue2
 cycle2:
push mainab
call outnum

push offset L23
call outstr
	push mainab
	push L3
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop mainab

	mov edx, mainab
	cmp edx, L22
	jnz cycle2
continue2:
push offset L24
call outstrline

push offset L23
call outstrline

push mainab
call outnumline
call system_pause
push 0
call ExitProcess
main ENDP
end main