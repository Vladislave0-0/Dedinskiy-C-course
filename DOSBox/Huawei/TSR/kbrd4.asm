.286
.model tiny
.code
org 100h
LOCALS @@

Start:      
            mov ax, 3509h                   ; 35 функция 21 прерывания: дать вектор прерывания. AH = 35h, AL = 09h - номер прерывания (keyboard)
            int 21h
            mov Old09Ofs, bx
            mov bx, es
            mov Old09Seg, bx


            push 0                          ; ES = 0h
            pop es

            mov bx, 4*09h                   ; segment offset
            cli                             ; запрет прерывания пока меняем 0000:0024 на адрес процедуры и на сегмент
            mov es:[bx], offset New09       ; говорим выполнять нашу процедуру, когда нажимается клавиша
            push cs                         ; говорим, что New09 в data segment
            pop ax                        
            mov es:[bx+2], ax
            sti                             ; разрешаем прерывание

            mov ax, 3100h                   ; 31 функция 21 прерывания - делаем программу резидентной с выделением памяти не на весь сегмент, а только на размер код программы
            mov dx, offset EOP              ; адресс конца программы
            shr dx, 4                       ; DX /= 16. 31 функция 21 прерывания ожидает количество 16-байтных параграфов
            inc dx                          ; чтобы не потерять последний параграф программы
            int 21h                         ; выполняем прерывание




New09       proc
            push ax bx es                   ; сохраняем ax, bx, es
            push 0b800h                     ; es в data segment
            pop es
            mov bx, cs:PrintOfs             ; положение символа
            mov ah, 4ch                     ; аттрибут

            in al, 60h                      ; читаем из 60h порта
            cmp al, 2d
            jne @@Here
            mov es:[bx], ax                 ; печатаем
            add bx, 2
            and bx, 0FFh
            mov cs:PrintOfs, bx
@@Here:
            pop es bx ax                    ; восстанавливаем ax, bx, es

            db 0EAh                         ; far jmp Old09Seg:Old09Ofs
Old09Ofs    dw 0                            ; offset of old 09h interruption
Old09Seg    dw 0                            ; segment of old 09h inrerruption
PrintOfs    dw 0                            ; смещение для переноса печати

            endp

EOP:

end Start
