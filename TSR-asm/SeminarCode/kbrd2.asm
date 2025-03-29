.286
.model tiny
.code
org 100h

Start:      push 0
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
            mov bx, (80*5+40)*2             ; положение символа
            mov ah, 4eh                     ; аттрибут

            in al, 60h                      ; читаеи из 60h порта
            mov es:[bx], ax                 ; печатаем

            in al, 61h                      ; данные из порта 61h в al
            or al, 80h                      ; ставим старший бит 61h в 1 => блокируем ее
            out 61h, al                     ; 
            and al, not 80h                 ; 
            out 61h, al                     ; ставим старший бит 61h в 0

            mov al, 20h                     ; end of interrupt
            out 20h, al                     ; в порт 20h кладем EOI

            pop es bx ax                    ; восстанавливаем ax, bx, es
            iret                            ; конец программного прерывания (обязательно)
            endp

EOP:

end Start
