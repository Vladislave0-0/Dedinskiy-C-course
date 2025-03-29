.model tiny
.286
.code
org 100h

Start:
	mov bx, 0b800h			; setting the offset of the vmem segment
	mov es, bx			; setting the offset to the es register
	mov bx, (80*9 + 80/2)*2		; the place of the future printing of the synbol 

	mov byte ptr es:[bx], 'A'	; printing char 'A' with segment in es and offset in bx
	mov byte ptr es:[bx+1], 2ch	; setting sttributes to char 'A': 2ch = 01001100b. Means that color of 'A' is intensity red with green background

	mov ax, 4c00h			; DOS func 4ch (Exit), exit code 00h			
	int 21h				; interraption

end 	Start
	