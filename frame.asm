.model tiny				; the directive indicating the size of the valiable memory segment
.code					; the directive of the beginning of the code segment
.186 					; the directive that defines which processor version the code is instended for
org 100h				; location in the memory of the first command
LOCALS @@               ; directive for local labels

;========================================================================================================================

SCREEN_WIDTH  equ 160d
SCREEN_HEIGHT equ 25d
VMEM_SEGMENT  equ 0b800h
H_OFFSET      equ SCREEN_WIDTH*5


EXIT	macro
		nop
		mov ax, 4c00h
		int 21h
		nop
		endm

;=======================================================================================================================
; string example for running the code: frame.com   a       b        c           d         e         &
;                                      ^           ^       ^        ^           ^         ^         ^
;                                      prog_name   width   height   attribute   pattern   message   endL
;=======================================================================================================================

Start:
        mov bx, VMEM_SEGMENT
        mov es, bx
        xor bx, bx

        call ParseString
        call PrintFrame

        xor ax, ax              ; waits for the key to be pressed
        mov ah, 08h
        int 21h

        EXIT



;===============================================================================
; Parses the entered string.
;-------------------------------------------------------------------------------
; Enter:    None
; Exit:     None
; Expects:  ES = 0b800h
; Destroys: None
;===============================================================================
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
                inc si                 ; skip 'h' in end of hex num
                call SkipSpaces

                call ParsePattern      ; parsing pattern


                xor dx, dx             ; save pattern type in DH
                mov dh, al

                pop ax                 ; save attribute in DL
                mov dl, al

                pop ax                 ; save height in BH
                mov bh, al

                pop ax                 ; save width in BL
                mov bl, al

			    ret
			    endp	



;===============================================================================
; Parses the type of pattern (programm or user-defined).
;-------------------------------------------------------------------------------
; Enter:    SI - pointer to pattern part of cmd line adress
; Exit:     AX - type of pattern
; Expects:  None
; Destroys: None
;===============================================================================
ParsePattern    proc

                lodsb
                cmp al, '*'         ; if(AL == '*') {goto UserPattern}
                jz @@UserPattern    ; else {use programm pattern}
                sub al, '1'
                jmp @@PatternExit

@@UserPattern:  mov ax, 4d

@@PatternExit:  ret
			    endp	



;===============================================================================
; Parses the entered decimal number from ASCII.
;-------------------------------------------------------------------------------
; Enter:    SI - pointer to part with dec of cmd line adress
; Exit:     AX - number
; Expects:  None
; Destroys: AX, BX, CX, DX
;===============================================================================
ParseDec        proc

                push si di          ; save registers
                mov di, si          ; DI = SI
                mov dx, 1d          ; DX = 1
                xor ax, ax          ; AX = 0
                xor bx, bx          ; BX = 0
                xor cx, cx          ; CX = 0

@@ReadLen:      lodsb               ; todo call strlen
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
                sub al, '0'         ; from ASCII to number
                push dx             ; save DX
                mul dx              ; AX *= 10^(digit-1)
                pop dx              ; saved DX
                add bx, ax          ; BX += AX
                mov ax, dx          ; DX *= 10
                mul cx              ; AX *= CX
                mov dx, ax          ; DX = AX
                dec di              ; DI--
                jmp @@NextDigit

@@EndNum:       pop cx di si        ; saved registers
                add si, cx          ; SI += len of number
                mov ax, bx          ; AX = BX

			    ret
			    endp



;===============================================================================
; Parses the entered hexagonal number.
;-------------------------------------------------------------------------------
; Enter:    SI - pointer to part with hex of cmd line adress
; Exit:     AX - number
; Expects:  None
; Destroys: AX, BX, CX, DX
;===============================================================================
ParseHex        proc

                push si di          ; saved registers
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
                sub al, 'a' - 0Ah   ; from ASCII to hex 
                jmp @@IsLetter


@@IsNumber:     sub al, '0'         ; from ASCII to hex
@@IsLetter:     push dx             ; save DX
                mul dx              ; AX *= 16^(digit-1)
                pop dx              ; saved DX
                add bx, ax          ; BX += AX
                mov ax, dx          ; DX *= 16
                mul cx              ; AX *= CX
                mov dx, ax          ; DX = AX
                dec di              ; DI--
                jmp @@NextDigit


@@EndNum:       pop cx di si        ; saved registers
                add si, cx          ; SI += len of number
                mov ax, bx          ; AX = BX

			    ret
			    endp



;===============================================================================
; Skips all spaces.
;-------------------------------------------------------------------------------
; Enter:    SI - pointer to part of cmd line adress
; Exit:     new SI with skipped spaces
; Expects:  None
; Destroys: None
;===============================================================================
SkipSpaces      proc

@@Next:         lodsb               ; AL = DS:[SI++]
                cmp al, ' '         ; if AL == ' ' then ZF = 1
                jz @@Next

                dec si              ; SI--

			    ret
			    endp



;===============================================================================
; Prints frame.
;-------------------------------------------------------------------------------
; Enter:    BL - width, BH - height
;           DL - attribute, DH - pattern
; Exit:     None
; Expects:  ES = 0b800h
; Destroys: AX, DI
;===============================================================================
PrintFrame  proc

            push bx dx si       ; save registers
            mov ah, dl          ; AH = attribute
            cld                 ; DF = 0 => DI++


            ; PATTERN SELECTION
            cmp dh, 4           ; if(pattern is wrong (type > 1 or type < 0))
            ja @@ErrPtrn        ; {goto ErrorPattern}
            cmp dh, 0
            jb @@ErrPtrn 
            cmp dh, 4           ; if the pattern is custom
            jz @@UserPtrn       ; if program pattern
            jmp @@ProgPtrn

@@ProgPtrn: call ProgPattern
@@UserPtrn: xor dx, dx          ; DX = 0
            mov dl, bl          ; for (CX - counter)


            mov di, SCREEN_WIDTH/2 + H_OFFSET - 2d  ; start position of printout
            push ax                                 ; save AX
            xor ax, ax                              ; AX = 0
            mov al, bl                              ; AL = Bl
            sub di, ax                              ; DI -= Ax
            pop ax                                  ; saved Ax


            ; FRAME PRINTOUT
            call PrintLine      ; prints first line
                                            
            xor cx, cx          ; prints middle lines
            mov cl, bh          ; CX = height*2 - 4
            shl cx, 1           ; CX *= 2
            sub cx, 4d          ; CX -= 4
@@GetChrs:  call PrintLine
			dec cx		        ; CX--
            sub si, 3           ; SI -= 3 for looping pattern
			loop @@GetChrs
            add si, 3           ; for 3 last chrs in pattern

            call PrintLine      ; prints last line


            pop si              ; saved SI
            pop dx              ; saved DX
            pop bx              ; saved BX


            ; USER MESSAGE PRINTOUT
            cmp dh, 4                   ; if(DH == 4) {skip 9 symbols}
            jz @@PrntMsg1               ; else {skip 1 symbol}
            inc si                      ; SI++
            jmp @@PrntMsg2

@@PrntMsg1: add si, 9                   ; if pattern from user, then skip all pattern
@@PrntMsg2: call SkipSpaces
            call PrintMsg

@@ErrPtrn:  ret
			endp	



;===============================================================================
; Prints user's message in the middle of the frame.
;-------------------------------------------------------------------------------
; Enter:    BL - width, BH - height
;           DL - attribute, DH - pattern
; Exit:     None
; Expects:  SI - pointer to user message
; Destroys: AX, BX
;===============================================================================            
PrintMsg    proc

            push cx di dx si    ; save registers   
            xor cx, cx          ; CX = 0
            xor di, di          ; DX = 0


            ; COUNTING LENGTH OF USER MESSAGE
@@CntLen:   lodsb               ; AL = DS:[SI++]
            cmp al, '&'         ; if(AL == '&') {goto ExitLen}
            jz @@ExitLen        ; else {goto CountLen}
            inc cx
            jmp @@CntLen
@@ExitLen:  pop si              ; saved SI

            ; CALCULATION OF MESSAGE OFFSET
            and cx, 0fffeh                      ; CX is even to access an even cell of video memory
            sub di, cx                          ; DI -= CX
            add di, H_OFFSET + SCREEN_WIDTH/2   ; DI += offset from the top
            xor cx, cx                          ; CX = 0
            and bx, 0feffh                      ; lower bit of BH = 0
            mov cl, bh                          ; CL = BH
            mov ax, SCREEN_WIDTH/2              ; AX = 80d
            mul cx                              ; AX *= CX
            add di, ax                          ; DI += AX
            and di, 0fffeh                      ; make DI even

            pop dx                              ; save DX
            mov ah, dl                          ; AH = DL


            ; PRINTOUT OF MESSAGE
@@Next:     lodsb           ; AL = DS:[SI++]
            cmp al, '&'     ; if(AL == '&') {goto Exit}
            jz @@Exit       ; else {print symbol; loop}
            stosw           ; ES:[DI] = AX, DI += 2
            jmp @@Next


@@Exit:  	pop di cx       ; save DI, CX

            ret
			endp	


        
;===============================================================================
; Sets the desired offset to print the desired pattern.
;-------------------------------------------------------------------------------
; Enter:    DH - type number of the programm pattern
; Exit:     SI - offset of control string
; Expects:  DH - type of pattern
; Destroys: None
;===============================================================================
ProgPattern proc

            push ax                         ; save AX
            xor ax, ax                      ; AX = 0

            mov al, dh                      ; AL = DH
            push dx                         ; save DX
            mov dh, 9d                      ; DH = 9
            mul dh                          ; AX *= 9
            pop dx                          ; saved DX
            mov si, offset control_string
            add si, ax                      ; SI += AX

            pop ax                          ; saved AX

			ret
			endp	



;===============================================================================
; Draws one line of the frame.
;-------------------------------------------------------------------------------
; Enter:    DX - counter for middle elements
;           DI - vmem position on screen
;           SI - source of frame element
; Exit:     None
; Expects:  ES = 0b800h
; Destroys: AX
;===============================================================================
PrintLine   proc

		    push di cx              ; save registers
            mov cx, dx              ; CX = DX

            ; LEFT CHARACTER
            lodsb                   ; AL = DS:[SI++]
            stosw                   ; ES:[DI] = AX, DI += 2

            ; MIDDLE CHARACTERS
            lodsb                   ; AL = DS:[SI++]
            rep stosw               ; while(CX--) {ES:[DI] = AX; DI += 2;}

            ; RIGHT CHARACTER
            lodsb                   ; AL = DS:[SI++]
            stosw                   ; ES:[DI] = AX, DI += 2

            pop cx di               ; saved registers
            add di, SCREEN_WIDTH    ; DI += 160 for next line

		    ret
			endp	



;===============================================================================
control_string  db 218d, 196d, 191d, 179d, ' ', 179d, 192d, 196d, 217d
                db 201d, 205d, 187d, 186d, ' ', 186d, 200d, 205d, 188d
                db  '+', 196d,  '+', 179d, ' ', 179d,  '+', 196d,  '+'
                db   3d,   3d,   3d,   3d, ' ',   3d,   3d,   3d,   3d

end Start
