
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

;=================================================================
; Parses the entered string
;-----------------------------------------------------------------
; Enter:    
; Exit:     
; Expects:  
; Destroys: 
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



;=================================================================
; Parses the type of pattern(programmatic or user-defined)
;-----------------------------------------------------------------
; Enter:    SI - pointer to part of cmd line adress
; Exit:     AX - type of pattern
; Expects:  None
; Destroys: AX, BX, CX, DX, SI
;=================================================================
ParsePattern    proc

                lodsb
                cmp al, '1'             ; programmatic patterns
                jz @@Pattern1
                cmp al, '2'
                jz @@Pattern2
                cmp al, '3'
                jz @@Pattern3
                cmp al, '4'
                jz @@Pattern4
                cmp al, '*'             ; user-defined pattern
                jz @@UserPattern
                
                mov ax, 5d
                jmp @@PatternExit       ; unknown pattern - ERROR


@@Pattern1:     mov ax, 0d
                jmp @@PatternExit
@@Pattern2:     mov ax, 1d
                jmp @@PatternExit
@@Pattern3:     mov ax, 2d
                jmp @@PatternExit
@@Pattern4:     mov ax, 3d
                jmp @@PatternExit
@@UserPattern:  mov ax, 4d
                ;dec si                  ; because there no space between '*' and next cmd
                jmp @@PatternExit



@@PatternExit:  ret
			    endp	



;=================================================================
; Parses the entered decimal number
;-----------------------------------------------------------------
; Enter:    SI - pointer to part of cmd line adress
; Exit:     AX - number
; Expects:  None
; Destroys: AX, BX, CX, DX, SI
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
                mov dx, ax
                dec di              ; DI--
                jmp @@NextDigit

@@EndNum:       pop cx              ; saved CX
                pop di              ; saved DI
                pop si              ; saved SI
                add si, cx          ; SI += len of number
                mov ax, bx

			    ret
			    endp



;=================================================================
; Parses the entered hexagonal number
;-----------------------------------------------------------------
; Enter:    SI - pointer to part of cmd line adress
; Exit:     AX - number
; Expects:  None
; Destroys: AX, BX, CX, DX, SI
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
                mov dx, ax
                dec di              ; DI--
                jmp @@NextDigit


@@EndNum:       pop cx              ; saved CX
                pop di              ; saved DI
                pop si              ; saved SI
                add si, cx          ; SI += len of number
                mov ax, bx

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
SkipSpaces      proc

@@Next:         lodsb                
                cmp al, ' '         ; if AL == ' ' then ZF = 1
                jz @@Next

                dec si              ; SI--

			    ret
			    endp



;=================================================================
; Prints frame
;-----------------------------------------------------------------
; Enter:    BL - width, BH - height
;           DL - attribute, DH - pattern
; Exit:     None
; Expects:  ES = 0b800h
; Destroys: AX, DX, DI
;=================================================================
PrintFrame  proc

            push bx                                                ; save BX
            push dx                                                ; save DX
            mov ah, dl                                             ; frame attribute
            cld                                                    ; DF = 0 => DI++
            push si                                                ; save SI


            cmp dh, 4                                              ; pattern selection
            ja @@ErrPtrn                                           ; если паттерн программный: mov si, offset control_string + pattern_offset
            cmp dh, 4                                              ; если патерн пользовательский: значение si уже в нужном месте командной строки
            jz @@UserPtrn                                          ; иначе выходим на ошибку и ничего не печатаем
            jmp @@ProgPtrn


@@ProgPtrn:
            call ProgPattern
@@UserPtrn: xor dx, dx                                             ; DX = 0
            mov dl, bl                                             ; for (CX - counter)


            mov di, SCREEN_WIDTH/2 + H_OFFSET - 2                  ; start position of printout
            push ax
            xor ax, ax
            mov al, bl
            sub di, ax
            pop ax


            call PrintLine                  ; prints first line
                                            
            xor cx, cx                      ; prints middle lines
            mov cl, bh                      ; CX = height*2 - 4
            shl cx, 1
            sub cx, 4d
@@Next:		call PrintLine
			dec cx							; CX--
            sub si, 3                       ; SI -= 3 for looping pattern
			loop @@Next
            add si, 3                       ; for 3 last chrs in pattern

            call PrintLine                  ; prints last line


            pop si                          ; saved SI
            pop dx                          ; saved DX
            pop bx                          ; saved BX

@@ErrPtrn:
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
