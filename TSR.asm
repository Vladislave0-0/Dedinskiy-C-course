.286
.model tiny
.code
org 100h
LOCALS @@

;=====================================================================================================

FHEIGHT      equ 12d
FWIDTH       equ 13d
SCREEN_WIDTH equ 160d
VMEM_SEGMENT equ 0b800h
ATTR         equ 4ch
H_OFFSET     equ SCREEN_WIDTH*5

;=====================================================================================================

Start:
            pushf                       ; save IF
            cli                         ; IF = 0 (interrupts disabled)

            mov ax, 3509h               ; 35 func of 21 int: give the interrupt vector.
                                        ; ES:[BX] = the address of the interrupt handler
            int 21h                     ; AH = 035h, AL = 09h (keyboard)
            mov Old09Ofs, bx            ; old offset of the interrupt handler
            mov bx, es
            mov Old09Seg, bx            ; old segment of the interrupt handler

            push 0                      ; ES = 0000
            pop es

            mov bx, 4*09h               ; BX = 0024 (address if of int 09h in interrupt table)
            mov es:[bx], offset New09   ; ES:[BX] = &New09
            mov es:[bx+2], cs           ; New09 in data segment. But now ES = 0000 and CS = old_ES


            mov ax, 3508h               ; 35 func of 21 int: give the interrupt vector.
                                        ; ES:[BX] = the address of the interrupt handler
            int 21h                     ; AH = 035h, AL = 08h (timer)
            mov Old08Ofs, bx            ; old offset of the interrupt handler
            mov bx, es
            mov Old08Seg, bx            ; old segment of the interrupt handler

            push 0                      ; ES = 0000
            pop es
            mov bx, 4*08h               ; BX = 0020 (address if of int 09h in interrupt table)
            mov es:[bx], offset New08   ; ES:[BX] = &New08
            mov es:[bx+2], cs           ; New08 in data segment. But now ES = 0000 and CS = old_ES
            sti                         ; IF = 1 (interrupts enabled)
            popf                        ; saved IF


            mov ax, 3100h               ; 31 func of 21 int: we make the program resident with
                                        ; memory allocation not for the entire segment,
                                        ; but only for the size of the program code.
            mov dx, offset EOP          ; end of programm address
            shr dx, 4                   ; DX /= 16. Because to 31 function of 21 int needs
                                        ; to be sent the number of paragraphs
            inc dx                      ; in order not to accidentally lose the last
                                        ; paragraph of the program
            int 21h



;=====================================================================================================
; Intercepting a keyboard interrupt. Changes the state of the variable depending on the pressed key.
;-----------------------------------------------------------------------------------------------------
; Enter:    The address 19A4:00C1 of the interrupt handler has been changed to offset New8
; Exit:     None
; Expects:  None
; Destroys: None
;=====================================================================================================
New09       proc

            push ax bx cx dx si di bp sp ds es

            push cs                         ; DS in data segment
            pop ds

            mov bx, offset regs_mode        ; in show_regs_mode we save (01h if mode "on") or (00h if mode "off")

            in al, 60h                      ; reading from port 60h to AL

            cmp al, 2Ah                     ; 2Ah = lShift
            je @@FrameOn

            cmp al, 36h                     ; 36h = rShift
            jne @@ExitInt

            mov byte ptr [bx], 00h          ; mode "frame off"
            jmp @@ExitInt

@@FrameOn:  mov byte ptr [bx], 01h

@@ExitInt:  pop es ds sp bp di si dx cx bx ax

            db          0EAh    ; far jmp Old09Seg:Old09Ofs
            Old09Ofs    dw 0    ; offset of old 09h interruption
            Old09Seg    dw 0    ; segment of old 09h inrerruption

            endp



;=====================================================================================================
; Intercepting a timer interrupt. Prints the frame if the rShift has not been pressed.
;-----------------------------------------------------------------------------------------------------
; Enter:    The address 19A4:00C1 of the interrupt handler has been changed to offset New8
; Exit:     None
; Expects:  None
; Destroys: None
;=====================================================================================================
New08       proc

            push es ds sp bp di si dx cx bx ax  ; save regs

            push VMEM_SEGMENT                   ; ES in VMEM segment
            pop es
            push cs                             ; DS in data segment
            pop ds


	        mov bx, offset regs_mode            ; BX = &regs_mode
	        mov byte ptr al, [bx]               ; AL = *BX
            cmp al, 01h                         ; check if AL == 1d (1d == enabled frame)
            jne @@ExitInt


            call PrintFrame
            call PrintRegVal


@@ExitInt:  pop ax bx cx dx si di bp sp ds es   ; saved regs

            db          0EAh    ; far jmp Old08Seg:Old08Ofs
            Old08Ofs    dw 0    ; offset of old 08h interruption
            Old08Seg    dw 0    ; segment of old 08h inrerruption

            endp



;=====================================================================================================
; Prints registers values on the screen.
;-----------------------------------------------------------------------------------------------------
; Enter:    all registers are on the stack in order right order from AX to ES
; Exit:     None
; Expects:  ES = 0b800h
; Destroys: AX, BX, CX
;=====================================================================================================
PrintRegVal     proc

                push bp								; begin stack frame
			    mov bp, sp

                mov bx, H_OFFSET + SCREEN_WIDTH + SCREEN_WIDTH/2 - 2d   ; start position of printout


                push dx bp              ; save regs
                mov dx, 10d             ; registers number for printout
                add bp, 4d              ; BP += 4


@@Loop:         mov ax, [bp]            ; to ax mov ax (= bp + 4), bx (= bp + 6), cx...
                call HexToAscii
                dec dx                  ; DX--
                cmp dx, 0               ; check if DX == 0 (we have printed out all the registers)
                je @@Exit
                add bx, SCREEN_WIDTH    ; BX += 180d (moving to the next line)
                add bp, 2d              ; BP += 2
                jmp @@Loop


@@Exit:         pop bp dx               ; saved regs

			    mov sp, bp              ; end stack frame
			    pop bp

                ret
                endp



;=====================================================================================================
; Gets ASCII from hexagonical number. For example: from 5h gets '5' or from 0Ch gets 'C'.
;-----------------------------------------------------------------------------------------------------
; Enter:    AX - required number
; Exit:     None
; Expects:  None
; Destroys: None
;=====================================================================================================
HexToAscii  proc

            push bx cx dx si di             ; save registers

            mov cx, 16d                     ; CX = 16 (counter of bits offset)
            xor si, si                      ; SI = 0
            mov di, 0f000h                  ; DI = 0F000h. This is counter that cuts off a specific
                                            ; digit of a hex. Then it will be 0F00h, 0F0h, 0Fh


@@Loop:     mov dx, ax                      ; DX = required number
            and dx, di                      ; select the desired digit of the number
            sub cx, 4                       ; CX -= 4
            shr dx, cl                      ; DX /= CX^2
            cmp dx, 0ah                     ; if DX < 0Ah --> goto decimal
            jb @@Decimal                    ; else --> goto hex

            add dx, 37h                     ; offset of hex
            jmp @@Print
@@Decimal:  add dx, 30h                     ; offset of dec
@@Print:    mov byte ptr es:[bx], dl        ; print specific digit

            inc si                          ; SI++
            cmp si, 4                       ; checking how many digits have already been read
            je @@Exit
            shr di, 4                       ; DI /= 4^2
            add bx, 2                       ; BX += 2
            jmp @@Loop

@@Exit:     pop di si dx cx bx              ; saved registers

            ret
            endp



;=====================================================================================================
; Prints frame.
;-----------------------------------------------------------------------------------------------------
; Enter:    None
; Exit:     None
; Expects:  ES = 0b800h
; Destroys: AX, DX, DI, CX
;=====================================================================================================
PrintFrame  proc

            push si                                                 ; save SI
            xor ax, ax                                              ; AX = 0
            mov ah, ATTR                                            ; frame attribute
            cld                                                     ; DF = 0 => DI++
            mov si, offset pattern                                  ; pattern for printout
            mov dx, FWIDTH - 2                                      ; it will be CX counter in PrintLine
            mov di, SCREEN_WIDTH/2 - (FWIDTH/2)*2 + H_OFFSET - 2    ; start position of printout


            ; PRINTS FIRST LINE
            call PrintLine

            ; PRINTS MIDDLE LINES
			mov cx, FHEIGHT*2 - 4d		    ; CX = height - 2
@@Next:		call PrintLine
			dec cx							; CX--
            sub si, 3                       ; SI -= 3 for looping pattern
			loop @@Next
            add si, 3                       ; for 3 last chrs in pattern

            ; PRINTS LAST LINE
            call PrintLine
            pop si                          ; saved SI


            call PrintRegsName

			ret
			endp



;=====================================================================================================
; Prints a column of registers name.
;-----------------------------------------------------------------------------------------------------
; Enter:    DX - counter for middle elements
;           DI - vmem position on screen
;           SI - source of frame element
; Exit:     None
; Expects:  ES = 0b800h
; Destroys: None
;=====================================================================================================
PrintRegsName   proc

                push ax di si cx    ; save regs

                mov cx, 10d         ; there are 10 registers

                mov si, offset regs_name
                mov di, H_OFFSET + SCREEN_WIDTH + SCREEN_WIDTH/2 - 8d   ; gets position of printout
                mov ah, ATTR

@@NextChar:     lodsb                   ; AL = DS:[SI++]
                stosw                   ; ES:[DI] = AX, DI += 2
                lodsb                   ; AL = DS:[SI++]
                stosw                   ; ES:[DI] = AX, DI += 2
                sub di, 4               ; DI -= 4
                add di, SCREEN_WIDTH    ; DI += 180d
                dec cx                  ; CX--
                cmp cx, 0               ; check if CX == 0
                jne @@NextChar


                pop cx si di ax         ; saved regs

                ret
                endp



;=====================================================================================================
; Draws one line of the frame.
;-----------------------------------------------------------------------------------------------------
; Enter:    DX - counter for middle elements
;           DI - vmem position on screen
;           SI - source of frame element
; Exit:     None
; Expects:  ES = 0b800h
; Destroys: AX
;=====================================================================================================
PrintLine   proc

		    push di cx              ; save regs
            mov cx, dx

            ; LEFT CHARACTER
            lodsb                   ; AL = DS:[SI++]
            stosw                   ; ES:[DI] = AX, DI += 2

            ; MIDDLE CHARACTERS
            lodsb                   ; AL = DS:[SI++]
            rep stosw               ; while(CX--) {ES:[DI] = AX; DI += 2}

            ; RIGHT CHARACTER
            lodsb                   ; AL = DS:[SI++]
            stosw                   ; ES:[DI] = AX, DI += 2

            pop cx di               ; saved regs
            add di, SCREEN_WIDTH    ; DI += 160 for next line

		    ret
			endp



;=====================================================================================================

pattern     db 201d, 205d, 187d, 186d, ' ', 186d, 200d, 205d, 188d
regs_name   db 'ax', 'bx', 'cx', 'dx', 'si', 'di', 'bp', 'sp', 'ds', 'es'
regs_mode   db 00h
EOP:
end Start
