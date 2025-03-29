.model tiny				; the directive indicating the size of the valiable memory segment
.code					; the directive of the beginning of the code segment
.186 					; the directive that defines which processor version the code is instended for
org 100h				; location in the memory of the first command
LOCALS @@

;==========================================================================================================

FrmH equ 26d
FrmW equ 80d				; should be FrmW % 4 == 0


EXIT	macro
		nop
		mov ax, 4c00h
		int 21h
		nop
		endm

;=======================

Start:
	mov bx, 0b800h
	mov es, bx
	xor bx, bx

	call PrintFrame

	EXIT


;==========================================
; Prints frame
;------------------------------------------
; Entry:    None
; Exit:		None
; Expects:	ES = 0b800h
; Destroys:	???
;==========================================
PrintFrame	proc

			push ax							; save AX
			push 4bh						; background color

			xor ax, ax						; AX = 0
			mov cl, FrmW					; CL = widht
			shr cl, 1						; CL /= 2
			sub al, cl						; AL = -CL
			not ah							; AX = -CL/2
			add ax, (4*80+80/2)*2-2  		; AX = middle + offset - widht/2
			mov bx, ax						; BX = AX


											; PRINT FIRST LINE
			push 187d						; right symbol
			push 205d						; middle symbol
			push 201d						; left symbol
			call PrintLine
			pop ax							; clear stack
			pop ax							; clear stack
			pop ax							; clear stack


											; PRINT MIDDLE LINES
			mov cx, FrmH - 4d				; CX = height - 2
			push 186d						; right symbol
			push 20h						; middle symbol
			push 186d						; left symbol
@@Next:		call PrintLine
			dec cx							; CX--
			loop @@Next
			pop ax							; clear stack
			pop ax							; clear stack
			pop ax							; clear stack


											; PRINT LAST LINE
			push 188d						; right symbol
			push 205d						; middle symbol
			push 200d						; left symbol
			call PrintLine
			pop ax
			pop ax
			pop ax


			pop ax							; clear stack (background color)
			pop ax							; saved

			ret
			endp	


;========================================================
; Prints one line of the frame
;--------------------------------------------------------
; Entry:	BX - the beginning of the line printout
; Exit:   	
; Expects:	ES = 0b800h
; Destroys: 
;========================================================
PrintLine	proc

			push bp								; begin
			mov bp, sp

			push ax								; save AX
			xor ax, ax							; AX = 0
			mov ah, [bp+10]						; background
			mov al, [bp+4]						; left symbol
			mov es:[bx], ax	
			push bx								; save bx
			add bx, 2


			cld									; DF = 0 => DI++
			push cx
			mov cx, FrmW/2						; CX counter

			mov di, bx							; place chars at str beginning
			mov al, [bp+6]						; middle symbol
			rep stosw							; while(cx--) {es:[di] = ax; di += 2;}

			mov al, [bp+8]
			mov es:[di], ax


			pop cx								; saved CX
			pop bx								; saved
			add bx, 160							; BX += 160 for next line beginning
			pop ax								; saved AX

			mov sp, bp
			pop bp								; saved BP

			ret
			endp



end Start

