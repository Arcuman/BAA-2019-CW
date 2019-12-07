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

 rand PROTO 

 pow PROTO : DWORD, : DWORD
.const
	L1 BYTE 'x=', 0
	L2 BYTE 'y=', 0
	L3 SDWORD 2
	L4 SDWORD 3
	L5 SDWORD 5
	L6 SDWORD 10
	L7 BYTE 'c = ', 0
	L8 SDWORD 9
	L9 BYTE 'x = ', 0
	L10 SDWORD -9
	L11 BYTE 'y = ', 0
	L12 BYTE 'Just', 0
	L13 BYTE 'strx = ', 0
	L14 BYTE '1', 0
	L15 BYTE 'strm = ', 0
	L16 BYTE 'string', 0
	L17 BYTE 'stry = ', 0
	L18 SDWORD 1
	L19 BYTE 't = ', 0
	L20 BYTE 't1 = ', 0
	L21 SDWORD 52
	L22 BYTE ' ', 0
	L23 SDWORD 8
.data
	minc SDWORD 0
	mainx SDWORD 0
	mainy SDWORD 0
	mainc SDWORD 0
	mainstrx DWORD ?
	mainstrm DWORD ?
	mainstry DWORD ?
	maint SDWORD 0
	maint1 SDWORD 0
	mainab SDWORD 0

.code

min PROC minx :  SDWORD , miny :  SDWORD 

push offset L1
call outstr

push minx
call outnumline

push offset L2
call outstr

push miny
call outnumline
	mov edx, minx
	cmp edx, miny
	jnz wrong1
	jmp next1
wrong1:	push L3
	pop miny

next1:
push offset L1
call outstr

push minx
call outnumline

push offset L2
call outstr

push miny
call outnumline
	mov edx, minx
	cmp edx, miny
	jnz right2
	jmp next2
right2:	push L4
	pop minx

next2:
push offset L1
call outstr

push minx
call outnumline

push offset L2
call outstr

push miny
call outnumline
	push L5
	push L3
	pop eax
	pop ebx
	mul ebx
	push eax
	push L6
	push L3
	pop ebx
	pop eax
	cdq
	idiv ebx
	push eax
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop minc


push offset L7
call outstr

push minc
call outnumline
	mov eax, minc
	ret
min ENDP
main PROC
	push L8
	pop mainx


push offset L9
call outstr

push mainx
call outnumline
	push L10
	pop mainy


push offset L11
call outstr

push mainy
call outnumline
	push L10
	push L8
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop mainc


push offset L7
call outstr

push mainc
call outnumline
	push offset L12
	pop mainstrx


push offset L13
call outstr

push mainstrx
call outstrline
	push offset L14
	pop mainstrm


push offset L15
call outstr

push mainstrm
call outstrline
	push offset L16
	pop mainstry


push offset L17
call outstr

push mainstry
call outstrline
	push min
	push L18
	push L18
	pop edx
	pop edx
	pop edx
	push L18
	push L18
		call min
	push eax
	push L4
	pop ebx
	pop eax
	cdq
	idiv ebx
	push eax
	pop maint


push offset L19
call outstr

push maint
call outnumline
	push L4
	push maint
	pop eax
	pop ebx
	mul ebx
	push eax
	pop maint1


push offset L20
call outstr

push maint
call outnumline
	push L3
	pop maint1


push offset L20
call outstr

push maint
call outnumline

push mainab
call outnum

push offset L22
call outstr
	push mainab
	push L3
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push L3
	pop eax
	pop ebx
	mul ebx
	push eax
	push L3
	push L23
	pop ebx
	pop eax
	cdq
	idiv ebx
	push eax
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop mainab


push offset L22
call outstrline

push mainab
call outnumline
call system_pause
push 0
call ExitProcess
main ENDP
end main