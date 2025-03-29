
; string example 

.model tiny				; the directive indicating the size of the valiable memory segment
.code					; the directive of the beginning of the code segment
.186 					; the directive that defines which processor version the code is instended for
org 100h				; location in the memory of the first command
LOCALS @@

;==========================================================================================================

FHEIGHT      equ 10d
FWIDTH       equ 22d
SCREEN_WIDTH equ 160d
VMEM_SEGMENT equ 0b800h
BACK_COLOR   equ 4bh
H_OFFSET     equ SCREEN_WIDTH*5


EXIT	macro
		nop
		mov ax, 4c00h
		int 21h
		nop
		endm

;=================================================================

Start:
        mov bx, VMEM_SEGMENT
        mov es, bx
        xor bx, bx


        call ParseString
        call PrintFrame

        EXIT

;=================================================================
; Parses the entered string
;-----------------------------------------------------------------
; Enter:    
; Exit:     
; Expects:  
; Destroys: 
;=================================================================
ParseString     proc

                push ax
                push 0082h                ; command line start adress
                pop si

                call ParseNumber          ; parsing width
                mov bl, al

                call SkipSpaces

                call ParseNumber          ; parsing width
                mov bh, al

                pop ax
			    ret
			    endp	



;=================================================================
; Parses the entered decimal number
;-----------------------------------------------------------------
; Enter:    SI - pointer to part of cmd line adress
; Exit:     AX - number
; Expects:  None
; Destroys: AX
;=================================================================
ParseNumber     proc

                push bx             ; save BX
                push cx             ; save CX
                push dx             ; save DX
                push si             ; save SI
                push di             ; save DI
                mov di, si          ; DI = SI
                mov dx, 1d          ; DX = 1
                xor ax, ax          ; AX = 0
                xor bx, bx          ; BX = 0
                xor cx, cx          ; CX = 0

@@ReadLen:      lodsb
                inc cl              ; CL++ 
                cmp al, ' '         ; if AL == ' ' then ZF = 1 
                jnz @@ReadLen
                dec cl              ; CL--  
                push cx             ; save CX


                add di, cx          ; DI += CX
                dec di              ; DI--
                mov cx, 10d         ; CX = 10 


@@NextDigit:    mov si, di          ; pointer to the end of number
                lodsb
                cmp al, ' '         ; if AL == ' ' then ZF = 1 
                jz @@EndNum
                sub al, 30h         ; from ASCII to number
                push dx             ; save DX
                mul dx              ; AX *= 10^(digit-1)
                pop dx              ; saved DX
                add bx, ax          ; BX += AX
                mov ax, dx          ; DX *= 10
                mul cx
                mov dx, ax
                dec di              ; DI--
                jmp @@NextDigit

@@EndNum:       pop cx              ; saved CX
                pop di              ; saved DI
                pop si              ; saved SI
                add si, cx          ; SI += len of number
                pop dx              ; saved DX
                pop cx              ; saved CX
                mov ax, bx
                pop bx              ; saved BX

			    ret
			    endp



;=================================================================
; Skips all spaces
;-----------------------------------------------------------------
; Enter:    SI - pointer to part of cmd line adress
; Exit:     new SI with skipped spaces
; Expects:  None
; Destroys: None
;=================================================================
SkipSpaces     proc

@@Next:         lodsb                
                cmp al, ' '         ; if AL == ' ' then ZF = 1
                jz @@Next

                dec si              ; SI--

			    ret
			    endp



;=================================================================
; Prints frame
;-----------------------------------------------------------------
; Enter:    None
; Exit:     None
; Expects:  ES = 0b800h
; Destroys: AX, DX, DI
;=================================================================
PrintFrame  proc

            mov ah, BACK_COLOR                                     ; frame attribute
            cld                                                    ; DF = 0 => DI++
            push si                                                ; save SI
            mov si, offset control_string + 18d                          ; pattern for printout
            ;add si, 18d
            mov dx, FWIDTH                                         ; CX - counter


            mov di, (SCREEN_WIDTH - FWIDTH*2)/2 + H_OFFSET - 2     ; start position of printout


            call PrintLine                  ; prints first line

                                            ; prints middle lines
			mov cx, FHEIGHT*2 - 4d		    ; CX = height - 2
@@Next:		call PrintLine
			dec cx							; CX--
            sub si, 3                       ; SI -= 3 for looping pattern
			loop @@Next

            add si, 3                       ; for 3 last chrs in pattern
            call PrintLine                  ; prints last line


            pop si                          ; saved SI
			ret
			endp	



;=================================================================
; Draws one line of the frame
;-----------------------------------------------------------------
; Enter:    DX - counter for middle elements
;           DI - vmem position on screen
;           SI - source of frame element
; Exit:     None
; Expects:  ES = 0b800h
; Destroys: AX
;=================================================================
PrintLine   proc

		    push di                 ; save DI
		    push cx                 ; save CX
            mov cx, dx

            lodsb                   ; AL = DS:[SI++]
            stosw                   ; ES:[DI] = AX, DI += 2

            lodsb
            rep stosw

            lodsb
            stosw

            pop cx                  ; saved CX
            pop di                  ; saved DI
            add di, SCREEN_WIDTH    ; DI += 160 for next line

		    ret
			endp	




control_string  db 201d, 205d, 187d, 186d, ' ', 186d, 200d, 205d, 188d
                db 201d, 205d, 187d, 186d, ' ', 186d, 200d, 205d, 188d
                db   3d,   3d,   3d,   3d, ' ',   3d,   3d,   3d,   3d

end Start
