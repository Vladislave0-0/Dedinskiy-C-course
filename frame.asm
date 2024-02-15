
; string example for running the code: frame.com   a       b        c           d         e
;                                      ^           ^       ^        ^           ^         ^
;                                      prog_name   width   height   attribute   pattern   sentence

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

;=================================================================+++
; Parses the entered string
;-----------------------------------------------------------------
; Enter:    None
; Exit:     None
; Expects:  ES = 0b800h
; Destroys: None
;=================================================================
ParseString     proc

                push 0082h             ; command line start adress
                pop si


                call ParseDec          ; parsing width
                push ax
                call SkipSpaces

                call ParseDec          ; parsing height
                push ax
                call SkipSpaces

                call ParseHex          ; parsing attribute
                push ax
                inc si
                call SkipSpaces

                call ParsePattern      ; parsing pattern
                push ax


                xor dx, dx             ; save pattern type in DH
                pop ax
                mov dh, al

                pop ax                 ; save attribute in DL
                mov dl, al

                pop ax                 ; save height in BH
                mov bh, al

                pop ax                 ; save width in BL
                mov bl, al

			    ret
			    endp	



;=================================================================+++
; Parses the type of pattern (programm or user-defined)
;-----------------------------------------------------------------
; Enter:    SI - pointer to pattern part of cmd line adress
; Exit:     AX - type of pattern
; Expects:  None
; Destroys: None
;=================================================================
ParsePattern    proc

                lodsb
                cmp al, '*'
                jz @@UserPattern
                sub al, '1'
                jmp @@PatternExit

@@UserPattern:  mov ax, 4d

@@PatternExit:  ret
			    endp	



;=================================================================
; Parses the entered decimal number from ASCII
;-----------------------------------------------------------------
; Enter:    SI - pointer to part with dec of cmd line adress
; Exit:     AX - number
; Expects:  None
; Destroys: AX, BX, CX, DX
;=================================================================
ParseDec        proc

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
                mov dx, ax          ; DX = AX
                dec di              ; DI--
                jmp @@NextDigit

@@EndNum:       pop cx              ; saved CX
                pop di              ; saved DI
                pop si              ; saved SI
                add si, cx          ; SI += len of number
                mov ax, bx          ; AX = BX

			    ret
			    endp



;=================================================================
; Parses the entered hexagonal number
;-----------------------------------------------------------------
; Enter:    SI - pointer to part with hex of cmd line adress
; Exit:     AX - number
; Expects:  None
; Destroys: AX, BX, CX, DX
;=================================================================
ParseHex        proc

                push si             ; save SI
                push di             ; save DI
                mov di, si          ; DI = SI
                mov dx, 1d          ; DX = 1
                xor ax, ax          ; AX = 0
                xor bx, bx          ; BX = 0
                xor cx, cx          ; CX = 0

@@ReadLen:      lodsb
                inc cl              ; CL++ 
                cmp al, 'h'         ; if AL == 'h' then ZF = 1 
                jnz @@ReadLen
                dec cl              ; CL--  
                push cx             ; save CX


                add di, cx          ; DI += CX
                dec di              ; DI--
                mov cx, 16d         ; CX = 16


@@NextDigit:    mov si, di          ; pointer to the end of number
                lodsb
                cmp al, ' '         ; if AL == ' ' then ZF = 1 
                jz @@EndNum

                cmp al, ':'         ; check if it is number or letter
                jb @@IsNumber
                sub al, 57h         ; from ASCII to hex
                jmp @@IsLetter


@@IsNumber:     sub al, 30h         ; from ASCII to hex
@@IsLetter:     push dx             ; save DX
                mul dx              ; AX *= 16^(digit-1)
                pop dx              ; saved DX
                add bx, ax          ; BX += AX
                mov ax, dx          ; DX *= 16
                mul cx
                mov dx, ax          ; DX = AX
                dec di              ; DI--
                jmp @@NextDigit


@@EndNum:       pop cx              ; saved CX
                pop di              ; saved DI
                pop si              ; saved SI
                add si, cx          ; SI += len of number
                mov ax, bx          ; AX = BX

			    ret
			    endp



;=================================================================
; Skips all spaces.
;-----------------------------------------------------------------
; Enter:    SI - pointer to part of cmd line adress
; Exit:     new SI with skipped spaces
; Expects:  None
; Destroys: None
;=================================================================
SkipSpaces      proc

@@Next:         lodsb                
                cmp al, ' '         ; if AL == ' ' then ZF = 1
                jz @@Next

                dec si              ; SI--

			    ret
			    endp



;=================================================================
; Prints frame.
;-----------------------------------------------------------------
; Enter:    BL - width, BH - height
;           DL - attribute, DH - pattern
; Exit:     None
; Expects:  ES = 0b800h
; Destroys: AX, DI
;=================================================================
PrintFrame  proc

            push bx                                         ; save BX
            push dx                                         ; save DX
            mov ah, dl                                      ; frame attribute
            cld                                             ; DF = 0 => DI++
            push si                                         ; save SI


            ; PATTERN SELECTION
            cmp dh, 4                                       ; if pattern is wrong (type > 1 or type < 0)
            ja @@ErrPtrn
            cmp dh, 0
            jb @@ErrPtrn 
            cmp dh, 4                                       ; if the pattern is custom
            jz @@UserPtrn                                   ; if program pattern
            jmp @@ProgPtrn

@@ProgPtrn: call ProgPattern
@@UserPtrn: xor dx, dx                                      ; DX = 0
            mov dl, bl                                      ; for (CX - counter)


            mov di, SCREEN_WIDTH/2 + H_OFFSET - 2           ; start position of printout
            push ax
            xor ax, ax
            mov al, bl
            sub di, ax
            pop ax


            ; FRAME PRINTOUT
            call PrintLine                  ; prints first line
                                            
            xor cx, cx                      ; prints middle lines
            mov cl, bh                      ; CX = height*2 - 4
            shl cx, 1                       ; CX *= 2
            sub cx, 4d                      ; CX -= 4
@@GetChrs:  call PrintLine
			dec cx							; CX--
            sub si, 3                       ; SI -= 3 for looping pattern
			loop @@GetChrs
            add si, 3                       ; for 3 last chrs in pattern

            call PrintLine                  ; prints last line


            pop si                          ; saved SI
            pop dx                          ; saved DX
            pop bx                          ; saved BX


            ; USER MESSAGE PRINTOUT
            cmp dh, 4
            jz @@PrntMsg1
            inc si
            jmp @@PrntMsg2

@@PrntMsg1: add si, 9
@@PrntMsg2: call SkipSpaces
            call PrintMsg

@@ErrPtrn:  ret
			endp	



;=================================================================
; Prints user's message in the middle of the frame.
;-----------------------------------------------------------------
; Enter:    BL - width, BH - height
;           DL - attribute, DH - pattern
; Exit:     None
; Expects:  SI - pointer to user message
; Destroys: AX, BX
;=================================================================            
PrintMsg    proc

            push cx     
            push di
            push dx
            push si
            xor cx, cx
            xor di, di

@@CntLen:   lodsb
            cmp al, '&'
            jz @@ExitLen
            inc cx
            jmp @@CntLen
@@ExitLen:  dec cx
            pop si


            mov ah, dl
            shr cx, 1
            sub di, cx
            add di, H_OFFSET + 76d
            xor cx, cx
            mov cl, bh
            dec cx
            shr cx, 1
            mov ax, cx
            mov cx, SCREEN_WIDTH
            mul cx
            add di, ax
            and di, 65534d

            pop dx
            mov ah, dl
@@Next:     lodsb
            cmp al, '&'
            jz @@Exit
            stosw
            jmp @@Next


@@Exit:  	pop di
            pop cx
            ret
			endp	


        
;=================================================================
; Gets type of the programm pattern
;-----------------------------------------------------------------
; Enter: 
; Exit:     SI - offset of control string
; Expects:  DH - type of pattern
; Destroys: 
;=================================================================
ProgPattern proc

            push ax                          ; save AX
            xor ax, ax                       ; AX = 0

            mov al, dh                       ; AL = DH
            push dx
            mov dh, 9d                       ; DH = 9
            mul dh                           ; AX *= 9
            pop dx
            mov si, offset control_string
            add si, ax

            pop ax

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




control_string  db 218d, 196d, 191d, 179d, ' ', 179d, 192d, 196d, 217d
                db 201d, 205d, 187d, 186d, ' ', 186d, 200d, 205d, 188d
                db  '+', 196d,  '+', 179d, ' ', 179d,  '+', 196d,  '+'
                db   3d,   3d,   3d,   3d, ' ',   3d,   3d,   3d,   3d

end Start
