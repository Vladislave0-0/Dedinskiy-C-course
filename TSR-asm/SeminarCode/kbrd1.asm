.286
.model tiny
.code
org 100h

Start:      push 0b800h
            pop es
            mov bx, (80*5+40)*2
            mov ah, 4ch

Next:       in al, 60h              ; addr of keyboard scanning
            mov es:[bx], ax

            cmp al, 2d              ; until "1" is pressed
            jne Next
            ret

end Start
