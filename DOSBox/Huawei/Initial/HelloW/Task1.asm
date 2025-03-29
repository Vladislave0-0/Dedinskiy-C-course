.model tiny				; the directive indicating the size of the valiable memory segment
.code					; the directive of the beginning of the code segment
.186 					; the directive that defines which processor version the code is instended for
org 100h				; location in the memory of the first command

Start:
	mov ah, 09h			; AH = 09, AL remains the same
	mov dx, offset MeowStr		; DX = $MeowStr
	int 21h				; interraption, 09h function of int 21h displays a string
	mov ax, 4c13h			; DOS func 4ch (Exit), exitcode 13h (19d)
	int 21h				; interraption

MeowStr:				
	db "Meow", 0dh, 0ah, '$'	; CR ('\r', 0dh), LF ('\n', 0ah)

end Start				; end - the directive indicating the end of assebly, Start - setting the initial label